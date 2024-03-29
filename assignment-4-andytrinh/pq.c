
/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Andy Trinh
 * Email: Trinha@oregonstate.edu
 */

#include <stdlib.h>
#include "pq.h"
#include "assert.h"
#include "dynarray.h"
/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed t0o implement a priority queue.
 */
struct pq {
  struct dynarray* da;
  struct node* n;

};

struct node {
  void* value;
  int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->da = dynarray_create();
  assert(pq->da);
  return pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  dynarray_free(pq->da);
  free(pq);
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if(dynarray_size(pq->da) != 0){
     return 0;
   }
   else if (dynarray_size(pq->da) == 0){
     return 1;
   }
 }

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct node* n = malloc(sizeof(struct node));
  struct node* parent;
  n->value = value;
  n->priority = priority;
  percolate(pq->da, n, parent);
}

//helper function
void percolate(struct dynarray* da, struct node* n, struct node* parent) {
  int da_size = dynarray_size(da);
  if(da_size == 0) {
    dynarray_insert(da, -1, n);
  }
  else {
    dynarray_insert(da, -1, n);
    int index = dynarray_size(da) - 1;
    int bool = 1;
    while(bool == 1) {
      parent = dynarray_get(da, (index-1)/2);
      if (parent->priority > n->priority) {
        dynarray_set(da, index, parent);
        dynarray_set(da, (index-1)/2, n);
        index = (index - 1)/2;
      }
      else {
        bool = 0;
      }
    }
  }
}

//correct
void swap(struct node* child, struct node *parent){
    void *value = parent->value;
    int par_priority = parent->priority;
    parent->priority = child->priority;
    parent->value = child->value;
    child->priority = par_priority;
    child->value = value;
}

void perc_d(struct dynarray* da, int index) {
  int da_size = dynarray_size(da);
  int left = (index*2)+1; //index of left
  int right = (index*2)+2; //index of right
  struct node* n = dynarray_get(da, index);
  int a;
  if(right >= da_size) {
    if(left >= da_size){
      return 0;
    }
    else {
      a = left;
    }
  }
  else {
    struct node* l = dynarray_get(da, (index*2)+1);
    struct node* r = dynarray_get(da, (index*2)+2);
    //set indices
    if(l->priority <= r->priority) {
      a = left;
    }
    else {
      a = right;
    }
  }
  struct node* Min = dynarray_get(da, a);
  if(n->priority > Min->priority) {
    void* u = dynarray_get(da, index);
    void* v = dynarray_get(da, a);
    swap(u, v);
    index = a;
    perc_d(da, index);
  }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct node* n = dynarray_get(pq->da, 0);
  return n->value;
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct node* n = dynarray_get(pq->da, 0);
  return n->priority;
}

//helper function
void heapify(struct dynarray* da) {
  int da_size = dynarray_size(da);
  if(da_size > 0) {
    int last = dynarray_size(da)-1;
    void* v = dynarray_get(da, last);
    dynarray_set(da, 0, v);
    dynarray_remove(da, -1);
    int size = dynarray_size(da);
    if(dynarray_size(da) > 0) {
      perc_d(da, 0);
    }
  }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  void* v = pq_first(pq);
  struct node* delete = dynarray_get(pq->da, 0);
  free(delete);
  heapify(pq->da);
  return v;
}



                       
