#ifndef __QUEUE_H
#define __QUEUE_H

#ifndef __DATA_TYPE
#define __DATA_TYPE

typedef int DATA_TYPE;
#define DATA_C "%d"

#endif // __DATA_TYPE

typedef struct queue{
  Node *head;
  Node *tail;
  int size;
} Queue;

DATA_TYPE deque(Queue *);
Queue *enque(Queue *, DATA_TYPE);
int isEmpty(Queue *);
DATA_TYPE peek(Queue *);
void printQue(Queue *);

#endif // __QUEUE_H
