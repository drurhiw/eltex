#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/types.h>
#include <unistd.h> 

#define SEM_KEY_ID   65          
#define MAX_NUMBERS  10          
#define MAX_LINE_LEN 256         
#define FILENAME "data.txt"
#define SEM_KEY_FILE "semfile" 

int create()
{
    key_t key = ftok(SEM_KEY_FILE, SEM_KEY_ID);
    if (key == -1)
    {
        perror("error ftok");
        exit(1);
    }

    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("error sem");
        exit(1);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1)
    {
        perror("error semctl");
        exit(1);
    }

    return semid;
}

void random_line(char* line, size_t max_len)
{
    int count = rand() % MAX_NUMBERS + 1;
    line[0] = '\0';

    for (int i = 0; i < count; i++)
    {
        int num = rand() % 100;
        char buffer[4];
        snprintf(buffer, sizeof(buffer), "%d", num);
        strcat(line, buffer);

        if (i < count - 1)
        {
            strcat(line, " ");
        }
    }
}

void block_semaphore(int semid)
{
    struct sembuf operation;

    operation.sem_num = 0;
    operation.sem_op = -1;
    operation.sem_flg = 0;

    if (semop(semid, &operation, 1) == -1)
    {
        perror("error block");
        exit(1);
    }
}

void unblock_semaphore(int semid)
{
    struct sembuf operation;

    operation.sem_num = 0;
    operation.sem_op = 1;
    operation.sem_flg = 0;

    if (semop(semid, &operation, 1) == -1)
    {
        perror("error unblock");
        exit(1);
    }
}

void write_line(const char* filename, const char* line)
{
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        perror("error fopen");
        exit(1);
    }

    fprintf(file, "%s\n", line);
    fclose(file);
}


int main(int argc, char* argv[])
{
    srand(time(NULL) ^ getpid());

    int semid = create();
    char line[MAX_LINE_LEN];

    while(1)
    {
        random_line(line, sizeof(line));

        block_semaphore(semid);
        write_line(FILENAME, line);
        unblock_semaphore(semid);

        printf("Записано: %s\n", line);
        sleep(1);
    }

    return 0;
}
