#include "queue.h"

void add(PriorityQueue* q, int priority, const char* data)
{
    QueueNode* newNode = malloc(sizeof(QueueNode));

    if (!newNode)
    {
        printError();
    }

    newNode->priority = priority;
    newNode->data = strdup(data);
    newNode->next = NULL;

    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;

        return;
    }
    else
    {
        QueueNode* current = q->head; //текущий узел    
        QueueNode* prev = NULL; //предыдущий узел
        while(current != NULL && current->priority <= newNode->priority)
        {
            prev = current;
            current = current->next;
        }

        if (prev == NULL)
        {
            newNode->next = q->head;
            q->head = newNode;
        }
        else
        {
            prev->next = newNode;
            newNode->next = current;

            if (current == NULL)
            {
                q->tail = newNode;
            }
        }
        
    }
}

char* dequeue(PriorityQueue* q)
{
    if (q->head == NULL)
    {
        return NULL;
    }

    QueueNode* remove = q->head;
    q->head = remove->next;

    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    char* result = strdup(remove->data);
    free(remove->data);
    free(remove);

    return result;
}

char* dequeueByPriority(PriorityQueue* q, int priority)
{
    if (q->head == NULL)
    {
        return NULL;
    }

    QueueNode* current = q->head;
    QueueNode* prev = NULL;

    while (current)
    {
        if (current->priority == priority)
        {
            if (prev == NULL)
            {
                q->head = current->next;
                if (q->head == NULL)
                {
                    q->tail = NULL;
                }
            }
            else 
            {
                prev->next = current->next;
                if (current == q->tail)
                {
                    q->tail = prev;
                }
            }
        }

        char* result = strdup(current->data);
        free(current->data);
        free(current);
        return result;
    }

    return NULL;
}

char* dequeueMinPriority(PriorityQueue* q, int minPriority)
{
    if (q->head == NULL)
    {
        return NULL;
    }

    QueueNode* current = q->head;
    QueueNode* prev = NULL;

    while (current != NULL && current->priority < minPriority)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return NULL;
    }

    if (prev == NULL)
    {
        q->head = current->next;
        if (q->head == NULL)
        {
            q->tail == NULL;
        }
    }
    else
    {
        prev->next = current->next;
        if (current == q->tail)
        {
            q->tail = prev;
        }
    }
    char* result = strdup(current->data);
    free(current->data);
    free(current);
    return result;

}

void printError()
{
    printf("Ошибка");
}

void printQueue(const PriorityQueue* q)
{
    if (q->head == NULL) {
        printf("Очередь пуста.\n");
        return;
    }

    printf("Очередь:\n");

    QueueNode* current = q->head;
    while (current != NULL) {
        printf("Приоритет: %d, Данные: %s\n", current->priority, current->data);
        current = current->next;
    }
}

void freeQueue(PriorityQueue* q)
{
    QueueNode* current = q->head;
    while (current != NULL)
    {
        QueueNode* temp = current;
        current = current->next;

        free(temp->data);
        free(temp);
    }

    q->head = NULL;
    q->tail = NULL;
}