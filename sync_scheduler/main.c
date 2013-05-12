#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <string.h>

ucontext_t* queue[4096];
size_t queue_head = 0;
size_t queue_tail = 0;
void enqueue(ucontext_t* i)
{
    queue[queue_head] = i;
    queue_head++;

    if (queue_head == 4096)
        queue_head = 0;
}

ucontext_t* dequeue()
{
    ucontext_t* result = queue[queue_tail];
    queue_tail++;

    if (queue_tail == 4096)
        queue_tail = 0;

    return result;
}

int empty()
{
    return queue_head == queue_tail;
}

struct itimerval it;
void alarm_sleep()
{
    memset(&it, 0, sizeof(struct itimerval));
    it.it_value.tv_usec = 1000;
    setitimer(ITIMER_REAL, &it, NULL);
}

ucontext_t scheduler_context;
void scheduler(int j, siginfo_t *siginfo, void *c)
{
    ucontext_t* old_context = (ucontext_t *) c;
    if (old_context != NULL)
        enqueue(old_context);

    if (! empty() )
    {
        ucontext_t* context = dequeue();
        alarm_sleep();
        setcontext(context);
    }
    else
    {
        exit(0);
    }
}

char scheduler_stack[4096];
sigset_t sigset;
void init_scheduler()
{
    getcontext(&scheduler_context);
    scheduler_context.uc_stack.ss_sp = scheduler_stack;
    scheduler_context.uc_stack.ss_size = sizeof(scheduler_stack);
    sigemptyset(&scheduler_context.uc_sigmask);
    makecontext(&scheduler_context, (void(*)(void))scheduler, 3, NULL, NULL, NULL);


    struct sigaction alarm_action;
    memset(&alarm_action, 0, sizeof(struct sigaction)); 
    sigemptyset(&alarm_action.sa_mask);
    alarm_action.sa_sigaction = scheduler;
    alarm_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    sigaction(SIGALRM, &alarm_action, NULL);
}

int runned = 0;
void run_scheduler()
{
    ucontext_t runner_context;
    init_scheduler();

    scheduler_context.uc_link = &runner_context;
    getcontext(&runner_context);
    if (! runned )
    {
        runned = 1;
        setcontext(&scheduler_context);
    }
}

void test(int i)
{
    size_t j = 0;
    size_t k = 0;
    size_t a = 0;
    size_t b = 0;
    printf("%d!\n",i);
    for (j = 0; j < i * 1000; ++j)
    {
        for (k = 0; k < 100000; ++k)
        {
            b += k;
        }
        a += 1;
    }
    printf("%d:%d\n",i,a);
}

void create_process(void *foo, int arg)
{   
    ucontext_t* context = malloc(sizeof(ucontext_t));
    char* thread_stack = malloc(4096);
    if (thread_stack == NULL || context == NULL)
    {
        printf("malloc() fail\n");
        exit(1);
    }

    getcontext(context);
    context->uc_stack.ss_sp = thread_stack;
    context->uc_stack.ss_size = 4096;
    context->uc_link = &scheduler_context;
    makecontext(context, (void(*)(void))foo, 1, arg);
    enqueue(context);
}

int main()
{
    {
        int i;
        for (i = 0; i < 10; ++i)
        {
            create_process(test, i);
        }
    }
    run_scheduler();
    return 0;
}
