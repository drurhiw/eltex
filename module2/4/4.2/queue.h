#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode
{
    int priority;
    char* data;
    struct QueueNode* next;
} QueueNode;

typedef struct PriorityQueue
{
    QueueNode* head;
    QueueNode* tail;
} PriorityQueue;

void add(PriorityQueue* q, int priority, const char* data);
char* dequeue(PriorityQueue* q);
char* dequeueByPriority(PriorityQueue* q, int priority);
char* dequeueMinPriority(PriorityQueue* q, int minPriority);
void printError();
void printQueue(const PriorityQueue* q);
void freeQueue(PriorityQueue* q);

#endif //QUEUE_H