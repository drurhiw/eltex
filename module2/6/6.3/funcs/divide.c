#include <stdarg.h>
#include <stdlib.h>

double divide(int n, ...)
{
    va_list factor;
    va_start(factor, n);
    double result = va_arg(factor, double);
    for (int i = 1; i < n; i++)
    {
        double divideisor = va_arg(factor, double);
        if (divideisor == 0)
        {
            va_end(factor);
            exit(1);  
        }
        result /= divideisor;
    }
    va_end(factor);
    return result;
}