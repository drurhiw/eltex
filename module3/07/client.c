#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h> 

#define QUEUE_CLIENT_TO_SERVER "/queue_c2s"
#define QUEUE_SERVER_TO_CLIENT "/queue_s2c"
#define MAX_TEXT 256
#define EXIT_PR 1

void queues_client(mqd_t *mq_c2s, mqd_t *mq_s2c)
{
    // отправка серверу
    *mq_c2s = mq_open(QUEUE_CLIENT_TO_SERVER, O_WRONLY);
    if (*mq_c2s == (mqd_t)-1)
    {
        perror("error client->server");
        exit(EXIT_PR);
    }

    // получение сообщения от сервера
    *mq_s2c = mq_open(QUEUE_SERVER_TO_CLIENT, O_RDONLY);
    if (*mq_s2c == (mqd_t)-1)
    {
        perror("error server->client");
        exit(EXIT_PR);
    }

    printf("[CLIENT] Очереди открыты\n");
}

void receive_message(mqd_t mq, char* buffer, unsigned int *priority)
{
    ssize_t read = mq_receive(mq, buffer, MAX_TEXT, priority);

    if (read < 0)
    {
        perror("error receive");
        exit(EXIT_PR);
    }

    buffer[read] = '\0';
    printf("[RECEIVE] Получено сообщение (приоритет %u): %s\n", *priority, buffer);
}

void send_message(mqd_t mq, const char* message, unsigned int priority)
{
    size_t len = strlen(message);

    if (len > MAX_TEXT)
    {
        perror("error send");
        exit(EXIT_PR);
    }
    
    int res = mq_send(mq, message, len, priority);

    if (res == -1)
    {
        perror("error send");
        exit(EXIT_PR);
    }

    printf("[SEND] Отправлено сообщение (приоритет %u): %s\n", priority, message);
}

int main()
{
    mqd_t mq_c2s, mq_s2c;
    char buffer[MAX_TEXT + 1];
    unsigned int priority;

    queues_client(&mq_c2s, &mq_s2c);

    while(1)
    {
        printf("Введите сообщение для сервера (или 'exit' для выхода): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            perror("fgets");
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0;  // Убираем символ новой строки

        if (strcmp(buffer, "exit") == 0) {
            send_message(mq_c2s, "Клиент завершает работу", EXIT_PR);
            break;
        }

        send_message(mq_c2s, buffer, 0);

        receive_message(mq_s2c, buffer, &priority);

        if (priority == EXIT_PR)
        {
            printf("[CLIENT] Сервер завершил работу.\n");
            break;
        }

        
    }

    mq_close(mq_c2s);
    mq_close(mq_s2c);

    return 0;
}