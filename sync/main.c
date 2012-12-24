#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

volatile int counter = 0;
volatile int mutex = 0;
volatile int dummy;

void* Incremental(void* argument)
{
    for (int i = 0; i < 100000; ++i)
    {
        __asm volatile ("pusha");
        __asm volatile ("xorl %ecx, %ecx");
        __asm volatile ("incl %ecx");
        __asm volatile ("spin_lock_retry_inc:");
        __asm volatile ("mov %0, %%ebx" : : "r" (&mutex));
        __asm volatile ("xorl %eax,%eax");
        __asm volatile ("lock; cmpxchgl %ecx, (%ebx)");
        __asm volatile ("jnz spin_lock_retry_inc");
        __asm volatile ("popa");

        counter += 1;
        __asm volatile ("pusha");
        __asm volatile ("movl $0, (%0)" : : "r" (&mutex));
        __asm volatile ("popa");

    }
}

void* Decremental(void* argument)
{
    __asm("pusha");
    for (int i = 0; i < 100000; ++i)
    {
        __asm volatile ("pusha");
        __asm volatile ("xorl %ecx, %ecx");
        __asm volatile ("incl %ecx");
        __asm volatile ("spin_lock_retry_dec:");
        __asm volatile ("mov %0, %%ebx" : : "r" (&mutex));
        __asm volatile ("xorl %eax,%eax");
        __asm volatile ("lock; cmpxchgl %ecx, (%ebx)");
        __asm volatile ("jnz spin_lock_retry_dec");
        __asm volatile ("popa");
        counter -= 1;
        __asm volatile ("pusha");
        __asm volatile ("movl $0, (%0)" : : "r" (&mutex));
        __asm volatile ("popa");
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
