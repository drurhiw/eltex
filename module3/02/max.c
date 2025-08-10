#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    double max = strtod(argv[1], NULL);

    for (int i = 2; i < argc; i++)
    {
        double val = strtod(argv[i], NULL);
        if (val > max)
        {
            max = val;
        }
    }

    printf("Максимум: %.2f\n", max);
    return 0;
}