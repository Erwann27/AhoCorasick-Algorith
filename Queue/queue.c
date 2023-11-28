#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

typedef struct cqueue cqueue;

struct cqueue {
  const void *value;
  cqueue *next;
};

struct Queue {
  cqueue *head;
  cqueue *tail;
  size_t size;
};

Queue *create_queue(void){
    Queue *q = malloc(sizeof *q);
    if(q == NULL){
        return NULL;
    }
    q->head = NULL;
    q->size = 0;
    return q;
}

int queue_is_empty(Queue *q){
    return q->size == 0 ? 1 : 0;
}

void enque(Queue *q, const void *xptr){
    if(xptr == NULL){
        exit(EXIT_FAILURE);
    }
    cqueue *p = malloc(sizeof *p);
    if(p == NULL){
        exit(EXIT_FAILURE);
    }
    p->value = xptr;
    p->next = NULL;
    if(q->size == 0){
        q->head = p;
    } else {
        cqueue *prev = q->tail;
        prev->next = p;
    }
    q->tail = p;
    q->size += 1;
}

const void *dequeue(Queue *q){
    if(q->size == 0){
        exit(EXIT_FAILURE);
    }
    cqueue *p = q->head;
    q->head = p->next;
    const void *xptr = p->value;
    free(p);
    q->size -= 1;
    return xptr;
}

void dispose_queue(Queue **qptr){
    if(*qptr == NULL){
        exit(EXIT_FAILURE);
    }
    cqueue *p = (*qptr)->head;
    while (p != NULL){
        cqueue *t = p;
        p = p->next;
        free(t);
    }
    free(*qptr);
    *qptr = NULL;
}