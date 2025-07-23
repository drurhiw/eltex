#include "queue.h"

int main()
{
    PriorityQueue queue = {NULL,NULL};
    

    while (1)
    {
        char choice;
        int priority;
        char data[256];
        printf("Добавить(1)/извлечь элемент(2)/выход(3): ");
        scanf(" %c", &choice);

        if (choice == '3') {
            break;
        }

        if (choice == '1')
        {
            printf("Введите элемент: ");
            scanf(" %255s", data);
            printf("Введите приоритет: ");
            scanf("%d", &priority);
            add(&queue, priority, data);
            printQueue(&queue);
        }

        if (choice == '2')
        {
            char choice2;
            printf("1. Извлечь первый элемент в очереди \n");
            printf("2. Извлечь первый элемент с заданным приоритетом \n");
            printf("3. Извлечь первый элемент с приоритетом не ниже, чем заданный \n");
            scanf(" %c", &choice2);
            if (choice2 == '1')
            {
                dequeue(&queue);
                printQueue(&queue);
            }
            else if (choice2 == '2')
            {
                int pr;
                printf("Введите приоритет: ");
                scanf(" %d", &pr);
                dequeueByPriority(&queue, pr);
                printQueue(&queue);
            }
            else 
            {
                int pr2;
                printf("Введите приоритет: ");
                scanf(" %d", &pr2);
                dequeueMinPriority(&queue, pr2);
                printQueue(&queue);
            }
        }
    }
    freeQueue(&queue);
    return 0;
}