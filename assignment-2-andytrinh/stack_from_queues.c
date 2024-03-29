/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Andy Trinh
 * Email: Trinha@oregonstate.edu
 */

#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "stack_from_queues.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your stack and return a pointer to the stack structure.
 */
struct stack_from_queues* stack_from_queues_create() {
  struct stack_from_queues* s = malloc(sizeof(struct stack_from_queues));
  assert(s);
  s->q1 = queue_create();
  s->q2 = queue_create();
  return s;
}

/*
 * This function should free all of the memory allocated to a stack, including
 * the memory associated with each queue.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if stack is NULL.
 */
void stack_from_queues_free(struct stack_from_queues* stack) {
  assert(stack);
  free(stack->q1);
  free(stack->q2);
  free(stack);
}

/*
 * This function should return 0 if a stack is completely empty or 1 if there
 * is at least one element stored in the stack.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *
 * Return:
 *   Should return 1 if the stack is empty or 0 otherwise.
 */
int stack_from_queues_isempty(struct stack_from_queues* stack) {
  assert(stack);
  if(queue_isempty(stack->q1) && queue_isempty(stack->q2)) {
    return 1;
  }
  else
    return 0;
}

/*
 * Should push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *   value - the new value to be pushed onto the stack
 */
void stack_from_queues_push(struct stack_from_queues* stack, int value) {
  assert(stack);
  queue_enqueue(stack->q1, value);

}

/*
 * Should return a stack's top value without removing that value from the
 * stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack.
 */
int stack_from_queues_top(struct stack_from_queues* stack) {
  assert(stack);
  int val;
  while (!queue_isempty(stack->q1)) {
    val = queue_dequeue(stack->q1);
    queue_enqueue(stack->q2, val);
  }
  while (!queue_isempty(stack->q2)) {
   int v = queue_dequeue(stack->q2);
   queue_enqueue(stack->q1, v);
  }
  return val;


}


/*
 * Should remove the top element from a stack and return its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack before that value
 *   is popped.
 */
int stack_from_queues_pop(struct stack_from_queues* stack) {
  assert(stack);
  int val = queue_dequeue(stack->q1); //return the value of top element
  while (!queue_isempty(stack->q1)) {
    queue_enqueue(stack->q2, val);
    val = queue_dequeue(stack->q1);
 }

 while(!queue_isempty(stack->q2)) {
   int v = queue_dequeue(stack->q2);
   queue_enqueue(stack->q1, v);
 }

 return val;
}
                                                                                   
                                                                                                                                                              
                                                                                                                                  