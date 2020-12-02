#include <pthread.h>
#include "q.h"
#define STACK_SIZE 8192

queue *ReadyQ = NULL;
TCB_t *Curr_Thread = NULL;

int thread_id = 0;

void init_ready(){
    ReadyQ = newQueue();
}

void start_thread(void (*function)(void))
{
    void *stack = malloc(STACK_SIZE);
    TCB_t *item = malloc(sizeof(TCB_t));
    init_TCB(item, function, stack, STACK_SIZE);
    item->thread_id = thread_id++;
    AddQueue(ReadyQ, item);
    // allocate a stack (via malloc) of a certain size (choose 8192)
    //  allocate a TCB (via malloc)
    //  call init_TCB with appropriate arguments
    //  Add a thread_id (use a counter)
    //  call addQ to add this TCB into the “ReadyQ” which is a global header pointer
}

void run()

{ // real code

    Curr_Thread = DelQueue(ReadyQ);
    ucontext_t parent; // get a place to store the main context, for faking

    getcontext(&parent); // magic sauce

    swapcontext(&parent, &(Curr_Thread->context)); // start the first thread
}

void yield() // similar to run
{
    TCB_t *Prev_Thread;
    AddQueue(ReadyQ, Curr_Thread);
    Prev_Thread = Curr_Thread;
    Curr_Thread = DelQueue(ReadyQ);

    // ucontext_t prev_context = Prev_Thread->context;
    // ucontext_t curr_context = Curr_Thread->context;
    swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}