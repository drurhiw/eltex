#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h> 

#define QUEUE_CLIENT_TO_SERVER "/queue_c2s"
#define QUEUE_SERVER_TO_CLIENT "/queue_s2c"
#define MAX_TEXT 256
#define EXIT_PR 1

struct attr 
{
    long mq_flags;                 // блокирующий режим
    long mq_maxmsg;               // максимум 10 сообщений в очереди
    long mq_msgsize;        // макс. размер одного сообщения
    long mq_curmsgs;  
};

struct attr my_attr = {0, 10, MAX_TEXT, 0};

void queues(mqd_t *mq_c2s, mqd_t *mq_s2c)
{

    // сервер читает
    *mq_c2s = mq_open(QUEUE_CLIENT_TO_SERVER, O_CREAT | O_RDONLY, 0666, &my_attr);

    if (*mq_c2s == (mqd_t)-1)
    {
        perror("error c2s");
        exit(EXIT_PR);
    }

    // сервер пишет
    *mq_s2c = mq_open(QUEUE_SERVER_TO_CLIENT, O_CREAT | O_WRONLY, 0666, &my_attr);

    if (*mq_s2c == (mqd_t)-1)
    {
        perror("error s2c");
        exit(EXIT_PR);
    }

    printf("[SERVER] Очереди созданы и открыты\n");
}

void receive_message(mqd_t mq_c2s, char *buffer, unsigned int *priority)
{
    ssize_t read =mq_receive(mq_c2s, buffer, MAX_TEXT, priority);

    if (read < 0)
    {
        perror("error receive");
        exit(EXIT_PR);
    }
    buffer[read] = '\0';
    printf("[SERVER] Получено сообщение (приоритет %u): %s\n", *priority, buffer);
}

void send_message(mqd_t mq_s2c, const char *message, unsigned int priority)
{
    size_t len = strlen(message);
    if (len > MAX_TEXT)
    {
        perror("error send");
        exit(EXIT_PR);
    }
    int res = mq_send(mq_s2c, message, len, priority);
    if (res == -1) 
    {
        perror("error send");
        exit(EXIT_PR);
    }
    printf("[SERVER] Отправлено сообщение (приоритет %u): %s\n", priority, message);
}

int main()
{
     mqd_t mq_c2s, mq_s2c;
     char buffer[MAX_TEXT + 1];
     unsigned int priority;
     queues(&mq_c2s, &mq_s2c);

     while (1) {
        receive_message(mq_c2s, buffer, &priority);
        if (priority == EXIT_PR) {
            printf("[SERVER] Клиент запросил завершение.\n");
            send_message(mq_s2c, "Сервер завершает работу", EXIT_PR);
            break;
        }

        char response[MAX_TEXT + 1];
        snprintf(response, sizeof(response), "Сервер получил: %s", buffer);

        send_message(mq_s2c, response, 0);
    }

    mq_close(mq_c2s);
    mq_close(mq_s2c);
    mq_unlink(QUEUE_CLIENT_TO_SERVER);
    mq_unlink(QUEUE_SERVER_TO_CLIENT);

    printf("[SERVER] Очереди закрыты, сервер завершён.\n");
    return 0;
}