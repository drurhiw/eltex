#include "calculator2.h"

double sum(int n, ...)
{
    double result = 0;
    va_list factor;
    va_start(factor, n);
    for (int i = 0; i < n; i++)
    {
        result += va_arg(factor, double);
    }
    va_end(factor);
    return result;
}

double sub(int n, ...)
{
    va_list factor;
    va_start(factor, n);
    double result = va_arg(factor, double);
    for (int i = 1; i < n; i++)
    {
        result -= va_arg(factor, double);
    }
    va_end(factor);
    return result;
}

double mul(int n, ...)
{
    va_list factor;
    va_start(factor, n);
    double result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= va_arg(factor, double);
    }
    va_end(factor);
    return result;
}

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


