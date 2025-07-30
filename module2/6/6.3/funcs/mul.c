#include <stdarg.h>

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