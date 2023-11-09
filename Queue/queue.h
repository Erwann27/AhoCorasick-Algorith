#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Queue Queue;

// Create an empty queue
extern Queue *create_queue(void);

// Enqueue xptr in q
extern void enque(Queue *q, const void *xptr);

// Dequeue last element in queue
extern const void *dequeue(Queue *q);

// Dispose queue q
extern void dispose_queue(Queue **qptr);

#endif