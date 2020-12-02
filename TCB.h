#include <ucontext.h>
#include <string.h>

// typedef is used to avoid using the keyword struct while using TCB_t..keeping the typedef alias same for better readability.
// variable names are as mentioned in the requirements

typedef struct TCB_t
{
 struct TCB_t *prev_pointer;
 struct TCB_t *next_pointer;
 int thread_id;
 ucontext_t context;
} TCB_t;


// function signature as given in project requirements

void init_TCB(TCB_t *tcb, void *function, void *stackP, int stack_size)
{
 memset(tcb, '\0', sizeof(TCB_t));
 getcontext(&tcb->context);
 tcb->context.uc_stack.ss_sp = stackP;
 tcb->context.uc_stack.ss_size = (size_t) stack_size;
 makecontext(&tcb->context, function, 0); 
}

