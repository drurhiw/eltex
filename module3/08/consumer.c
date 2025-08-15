#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/types.h>
#include <unistd.h> 

#define SEM_KEY_ID   65            
#define MAX_LINE_LEN 256           
#define SEM_KEY_FILE "semfile" 

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


int read_and_remove(const char* filename, char* line, size_t max_len)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("error fopen");
        exit(1);
    }

    FILE* temp = fopen("temp.txt", "w");
    if (!temp)
    {
        perror("error fopen temp");
        fclose(file);
        return 0;
    }

    char buffer[256];
    int first_line = 1;

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (first_line)
        {
            first_line = 0;
            continue;
        }
        fputs(buffer, temp);
    }

    fclose(file);
    fclose(temp);

    if (remove(filename) != 0)
    {
        perror("error remove");
        return 0;
    }

    if (rename("temp.txt", filename) != 0)
    {
        perror("error rename");
        return 0;
    }

    return 1;
}

void search_min_max(const char* line)
{
    int min = 0;
    int max = 0;
    int first_number = 1;

    char temp[256];
    strncpy(temp, line, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    char* token = strtok(temp, " \t\n");
    while (token != NULL)
    {
        int num = atoi(token);
        if (first_number)
        {
            min = max = num;
            first_number = 0;
        }
        else
        {
            if (num < min)
            {
                min = num;
            }
            if (num > max)
            {
                max = num;
            }
        }

        token = strtok(NULL, " \t\n");
    }

    if (!first_number)
    {
        printf("Мин: %d, Макс: %d\n", min, max);
    }
    else
    {
        printf("В строке нет чисел\n");
    }
}

int main()
{
    key_t key = ftok(SEM_KEY_FILE, SEM_KEY_ID);
    if (key == -1)
    {
        perror("error ftok");
        return   1;
    }

    int semid = semget(key, 1, 0666);
    if (semid == -1)
    {
        perror("error semget");
        return 1;
    }

    while(1)
    {
        block_semaphore(semid);

        FILE* file = fopen("data.txt", "r");

        if (!file)
        {
            perror("error fopen");
            unblock_semaphore(semid);
            sleep(1); 
            continue;
        }

        char line[MAX_LINE_LEN];
        while (fgets(line, sizeof(line), file))
        {
            printf("Прочитана строка: %s", line);
            search_min_max(line);
        }
        fclose(file);

        unblock_semaphore(semid);
        sleep(1);
    }

    return 0;
}