// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include "threads.h"

typedef struct semaphore_t {
     queue *mutex_queue;
     int count;
} semaphore_t;

semaphore_t CreateSem(int i)
{
    semaphore_t *s = (semaphore_t *)(malloc(sizeof(struct semaphore_t))); 
    s->count = i;
    s->mutex_queue = newQueue();
    return *s;
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process 
 */
void P(semaphore_t *sem)
{   
    // pthread_mutex_lock (&(sem->mutex)); 
    sem->count--;
    if (sem->count < 0){
        AddQueue(sem->mutex_queue, Curr_Thread);
        TCB_t *Prev_Thread = Curr_Thread;
        Curr_Thread = DelQueue(ReadyQ);
        swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
    }
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */

void V(semaphore_t * sem)
{   
    sem->count++;
    if (sem->count <= 0) {
        AddQueue(ReadyQ, DelQueue(sem->mutex_queue));
    }
    yield();
}