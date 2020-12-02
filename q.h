#include <stdbool.h>
#include "TCB.h"

// typedef struct QElement
// {
//  struct QElement* prev_pointer;
//  struct QElement* next_pointer;
//  int payload;
// }qelement;

typedef struct queue
{
  TCB_t *head;
} queue;

// Returns a pointer to a new qelement
void *NewItem()
{
  return malloc(sizeof(TCB_t));
}

//creates a new queue and returns a pointer to the new queue. The nxt and previous pointers
queue *newQueue()
{
  queue *new_queue = malloc(sizeof(queue));
  new_queue->head = NULL;
  return new_queue;
}

void AddQueue(queue *queue, TCB_t *item)
{

  //printf("prinintg the payload inside the Add queue %d\n", item -> payload);
  if (queue->head == NULL)
  {
    queue->head = item;
    queue->head->prev_pointer = item;
    queue->head->next_pointer = item;
    //  printf("checking if isNUll works or not\n");
  }

  else
  {
    //  printf("inside general adds now\n");
    item->prev_pointer = queue->head->prev_pointer;
    item->next_pointer = queue->head;
    queue->head->prev_pointer->next_pointer = item;
    queue->head->prev_pointer = item;
  }
}

TCB_t *DelQueue(queue *queue)
{
  if (queue->head == NULL)
  {
    printf("no element in the queue to delete\n");
    return NULL;
  }

  else if (queue->head->next_pointer == queue->head)
  {
    TCB_t *head = queue->head;
    queue->head = NULL;
    return head;
  }

  else
  {
    queue->head->next_pointer->prev_pointer = queue->head->prev_pointer;
    queue->head->prev_pointer->next_pointer = queue->head->next_pointer;
    TCB_t *item_to_be_deleted = queue->head;
    queue->head = queue->head->next_pointer;

    item_to_be_deleted->next_pointer = NULL;
    item_to_be_deleted->prev_pointer = NULL;
    return item_to_be_deleted;
  }
}

// void print_queue(queue *queue)
// {
//   TCB_t *first_element = queue->head;
//   if (queue->head == NULL)
//   {
//     printf("nothing in queue to print\n");
//     return;
//   }
//   //  printf(" %d\n", queue -> head -> payload);
//   TCB_t *current_element = queue->head->next_pointer;
//   while (current_element != first_element)
//   {
//     // printf(" %d\n", current_element -> payload);
//     current_element = current_element->next_pointer;
//   }
// }