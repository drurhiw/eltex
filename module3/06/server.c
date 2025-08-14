#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

#define MAX_TEXT 256
#define QUEUE_PATH "server.c"
#define QUEUE_PROJ_ID 65

struct msgbuf 
{
    long mtype;
    int sender;
    char mtext[MAX_TEXT];
};

struct state
{
    int client[100];
    int count;
};

int queue()
{
    key_t key = ftok(QUEUE_PATH, QUEUE_PROJ_ID);
    if (key == -1)
    {
        perror("error frok");
        exit(1);
    }

    int ms = msgget(key, IPC_CREAT | 0666);
    if (ms == -1)
    {
        perror("error msgget");
        exit(1);
    }

    printf("[SERVER] Очередь создана/подключена. msqid = %d\n", ms);
    return ms;
}

void message_from_the_client(int ms, struct msgbuf* msbuf)
{
    ssize_t message = msgrcv(ms, msbuf, sizeof(struct msgbuf) - sizeof(long), 10, 0);

    if (message == -1)
    {
        perror("error msgrcv");
        exit(1);
    }
    printf("[SERVER] Получено сообщение от клиента %d: \"%s\"\n", msbuf->sender, msbuf->mtext);
}

int add_client(struct state* state, int new_client)
{
    for (int i = 0; i < state->count; i++)
    {
        if (state->client[i] == new_client)
        {
            return 0;
        }
    }
    if (state->count > 100)
    {
        return -1;
    }
    else
    {
        state->client[state->count++] = new_client;
        printf("[SERVER] Клиент %d добавлен. Всего клиентов: %d\n", new_client, state->count);
        return 1;
    }   
}

void remove_client(struct state* state, int IDclient)
{
    for (int i = 0; i < state->count; i++)
    {
        if (state->client[i] == IDclient)
        {
            for (int j = i; j < state->count - 1; j++)
            {
                state->client[j] = state->client[j+1];
            }
            state->count--;
            printf("[SERVER] Клиент %d удалён. Осталось клиентов: %d\n", IDclient, state->count);
            break;
        }
    }
}

void send_message(int ms, struct state* state, struct msgbuf* msbuf)
{
    int sender = msbuf->sender; //приоритет

    if (strcmp(msbuf->mtext, "shutdown") == 0)
    {
        printf("[SERVER] Клиент %d отправил shutdown\n", sender);
        remove_client(state, sender);
        return;
    }

    add_client(state, sender);
    for (int j = 0; j < state->count; j++)
    {
        if (state->client[j] != sender)
        {
            struct msgbuf out_msg;
            out_msg.mtype = state->client[j];
            out_msg.sender = sender; //запоминаем, кто написал сообщение
            strcpy(out_msg.mtext, msbuf->mtext);

            if (msgsnd(ms, &out_msg, sizeof(struct msgbuf) - sizeof(long), 0) == -1)
            {
                perror("error msgsnd");
            }
            else 
            {
                printf("[SERVER] Сообщение от %d отправлено клиенту %ld: \"%s\"\n", sender, out_msg.mtype, out_msg.mtext);
            }
        }
        
    }
}



int main()
{
    int ms = queue();
    struct msgbuf msbuf;
    struct state server_state = {0};

    printf("[SERVER] Ожидание сообщений...\n");
    
    while(1)
    {
        message_from_the_client(ms, &msbuf);
        send_message(ms, &server_state, &msbuf);
    }

    return 0;
}