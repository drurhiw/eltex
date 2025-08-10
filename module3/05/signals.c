#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

FILE *file = NULL; 

void openFile()
{
    file = fopen("output.log", "a");
    if (!file)
    {
        perror("error");
        exit(1);
    }
}

volatile sig_atomic_t Scount = 0;

void sign(int signo)
{
    if (signo == SIGINT)
    {
        Scount++;
        fprintf(file, "Получен и обработан сигнал SIGINT\n");
        fflush(file);
        if (Scount >= 3)
        {
            fprintf(file, "Третий SIGINT получен, завершаем программу.\n");
            fflush(file);
            fclose(file);
            exit(0);
        }
        
    }
    else if (signo == SIGQUIT)
    {
        fprintf(file, "Получен и обработан сигнал SIGQUIT\n");
        fflush(file);
    }
}

void regSIG(int signo)
{
    if (signal(signo, sign) == SIG_ERR)
    {
        perror("Ошибка регистрации сигнала");
        exit(1);
    }
}

int main()
{
    openFile();

    regSIG(SIGINT);
    regSIG(SIGQUIT);

    int counter = 1;
    while (1)
    {
        fprintf(file, "%d\n", counter++);
        fflush(file);
        sleep(1);
    }

    fclose(file);
    return 0;
}