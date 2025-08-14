#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
    long mtype;
    int sender;
    char mtext[256];
};

int connect_to_queue()
{
    key_t key = ftok("server.c", 65);
    if (key == -1)
    {
        perror("error frok");
        exit(1);
    }

    int ms = msgget(key, 0666);
    if (ms == -1)
    {
        perror("error msgget");
        exit(1);
    }

    return ms;
}

void send_message(int msqid, struct msgbuf* msg)
{
    msg->mtype = 10;

    if (msgsnd(msqid, msg, sizeof(struct msgbuf) - sizeof(long), 0) == -1) {
        perror("msgsnd error");
        exit(1);
    }
}

ssize_t receive_message(int msqid, struct msgbuf* msg, long mtype)
{
    ssize_t ret = msgrcv(msqid, msg, sizeof(struct msgbuf) - sizeof(long), mtype, 0);
    if (ret == -1)
    {
        perror("msgrcv error");
        exit(1);
    }
    
    return ret;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <client_id>\n", argv[0]);
        exit(1);
    }

    int client_id = atoi(argv[1]);
    int msqid = connect_to_queue();
    struct msgbuf msg;

    while (1)
    {
        printf("Введите сообщение (или 'exit' для выхода): ");
        fgets(msg.mtext, sizeof(msg.mtext), stdin);
        msg.mtext[strcspn(msg.mtext, "\n")] = 0;

        if (strcmp(msg.mtext, "exit") == 0)
        {
            printf("Выход из программы.\n");
            break;
        }

        msg.sender = client_id;
        send_message(msqid, &msg);

        receive_message(msqid, &msg, client_id);
        printf("Получено сообщение от %d: %s\n", msg.sender, msg.mtext);
    }

    return 0;
}