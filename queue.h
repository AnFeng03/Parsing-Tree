//
// Created by Andy Feng on 10/17/23.
//

#ifndef P2_QUEUE_H
#define P2_QUEUE_H


typedef struct QueueNode {
    TREE value;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

bool isEmpty(Queue* q);
void enqueue(Queue* q, TREE value);
TREE dequeue(Queue* q);

#endif //P2_QUEUE_H
