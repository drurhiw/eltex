#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    while(1)
    {
        char input[256];
        int i = 0;
        char *args[10];
        printf("Здравствуй, пользователь!\n");
        printf("Введите имя и аргумент: \n");
        fgets(input, sizeof(input), stdin);
        
        char *token = strtok(input, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();

        if (pid == 0)
        {
            execvp(args[0], args);
            exit(1);
        }
        else 
        {
            wait(NULL);
        }
        
    }

}