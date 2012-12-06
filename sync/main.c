#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int counter = 0;
int mutex = 0;
int dummy;

void* Incremental(void* argument)
{
    __asm("pusha");
    for (int i = 0; i < 100000; ++i)
    {
        __asm("xorl %ecx, %ecx");
        __asm("incl %ecx");
        __asm("spin_lock_retry_inc:");
        __asm("mov %0, %%ebx" : : "r" (&mutex));
        __asm("xorl %eax,%eax");
        __asm("lock; cmpxchgl %ecx, (%ebx)");
        __asm("jnz spin_lock_retry_inc");
        counter += 1;
        __asm("movl $0, (%0)" : : "r" (&mutex));
    }
    __asm("popa");
}

void* Decremental(void* argument)
{
    __asm("pusha");
    for (int i = 0; i < 100000; ++i)
    {
        __asm("xorl %ecx, %ecx");
        __asm("incl %ecx");
        __asm("spin_lock_retry_dec:");
        __asm("mov %0, %%ebx" : : "r" (&mutex));
        __asm("xorl %eax,%eax");
        __asm("lock; cmpxchgl %ecx, (%ebx)");
        __asm("jnz spin_lock_retry_dec");
        counter -= 1;
        __asm("movl $0, (%0)" : : "r" (&mutex));
    }
    __asm("popa");
}

int main()
{
    pthread_t threads[2];
    
    for (int count = 0; count < 100; ++count)
    {
        counter = 0;
        pthread_create(&threads[0], NULL, Incremental, NULL);
        pthread_create(&threads[1], NULL, Decremental, NULL);

        for (int i = 0; i < 2; ++i)
        {
            pthread_join(threads[i], NULL);
        }

        if (counter != 0)
        {
            printf("Fail\n");
            exit(-1);
        }
    }
    printf("Ok!\n");
}
