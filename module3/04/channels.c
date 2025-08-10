#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_CMDS 10
#define MAX_ARGS 10
#define BUF_SIZE 256
#define STDIN_FILENO 0
#define STDOUT_FILENO 1

typedef struct
{
    char *args[MAX_ARGS];
    char *input;
    char *output;
} Command;

int read_input(char *input)
{
    printf("Здравствуй, пользователь!\n");
    printf("Введите имя и аргумент: \n");

    if (!fgets(input, BUF_SIZE, stdin))
    {
        return 0;
    }
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0)
    {
        return 0;
    }
    return 1;
}

int split_by_pipes(char *input, char *cmd[])
{
    int count = 0;
    char *token = strtok(input, "|");
    while (token != NULL && count < MAX_CMDS)
    {
        while (*token == ' ')
        {
            token++;
        }
        cmd[count++] = token;
        token = strtok(NULL, "|");
    }
    return count;
}

void split_into_args(char *cmd_str, Command *cmd)
{
    int i = 0;
    cmd->input = NULL;
    cmd->output = NULL;


    char *token = strtok(cmd_str, " ");
    while (token && i < MAX_ARGS - 1)
    {
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " ");
            cmd->input = token;
        }
        else if (strcmp(token, ">") == 0) 
        {
            token = strtok(NULL, " ");
            cmd->output = token;
        }
        else
        {
            cmd->args[i++] = token;
        }
        if (token)
        {
            token = strtok(NULL, " ");
        }
    }
    cmd->args[i] = NULL;
}

void exe(Command cmd[], int countCMD)
{
    int pipes[MAX_CMDS - 1][2];

    for (int i = 0; i < countCMD - 1; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }

    for (int i = 0; i < countCMD; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if (cmd[i].input != NULL)
            {
                int fd = open(cmd[i].input, O_RDONLY);
                if (fd < 0)
                {
                    perror("open input file");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            else if (i > 0)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }

            if (cmd[i].output != NULL)
            {
                int fdout = open(cmd[i].output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fdout < 0)
                {
                    perror("open output file");
                    exit(1);
                }
                dup2(fdout, STDOUT_FILENO);
                close(fdout);
            }
            else if (i < countCMD - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < countCMD - 1; j++)
            {
                if (j != i - 1)
                {
                    close(pipes[j][0]);
                }
                if (j != i)
                {
                    close(pipes[j][1]);
                }
                
            }

            execvp(cmd[i].args[0], cmd[i].args);
            perror("execvp");
            exit(1);
        }
    }

    for (int i = 0; i < countCMD - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < countCMD; i++)
    {
        wait(NULL);
    }
}


int main()
{
    char input[BUF_SIZE];
    char *cmdstr[MAX_CMDS];
    Command cmd[MAX_CMDS];

    while (read_input(input))
    {
        int countCMD = split_by_pipes(input, cmdstr);

        for (int i = 0; i < countCMD; i++)
        {
            split_into_args(cmdstr[i], &cmd[i]);
        }

        exe(cmd, countCMD);
    }

    return 0;
}