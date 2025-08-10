#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

int number(const char* s, double *out)
{
    if (!*s)
    {
        return 0;
    }

    char *endptr;
    double val = strtod(s, &endptr);

    if (*endptr == '\0')
    {
        *out = val;
        return 1;
    }
    else
    {
        return 0;
    }
}

double mul(double x)
{
    return x * 2;
}

void get_range(int argc, int process_num, int *start, int *end)
{
    int total_args = argc - 1;
    int mid = total_args / 2;
    if (process_num == 0)
    {
        *start = 1;
        *end = mid;
    }
    else 
    {
        *start = mid + 1;
        *end = argc - 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Нет аргументов");
        return 0;
    }

    int start, end;
    pid_t pid = fork();

    if (pid < 0)
    {
        return 1;
    }
    if (pid == 0)
    {
        get_range(argc, 1, &start, &end);
    }
    else
    {
        get_range(argc, 0, &start, &end);
    }

    int i = start;
    while (i <= end)
    {
        double val;
        if (number(argv[i], &val))
        {
            double dou = mul(val);

            if (pid == 0) {
                printf("Process 1: %s -> %.2f * 2 = %.2f\n", argv[i], val, dou);
            } else {
                printf("Process 0: %s -> %.2f * 2 = %.2f\n", argv[i], val, dou);
            }
        }
        else 
        {
            if (pid == 0) {
                printf("Process 1: %s (not a number)\n", argv[i]);
            } else {
                printf("Process 0: %s (not a number)\n", argv[i]);
            }
        }
        i++;
    }

    if (pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
    

    return 0;
}