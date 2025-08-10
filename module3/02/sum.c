#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    double res = 0;
    for (int i = 1; i < argc; i++)
    {
        double str = strtod(argv[i], NULL);
        res += str;
    }

    printf("Сумма: %.2f\n", res);
}