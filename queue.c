#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "queue.h"

bool isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, TREE value) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->value = value;
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
}

TREE dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;
    QueueNode* temp = q->front;
    TREE value = temp->value;
    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}
