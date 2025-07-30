#include <stdarg.h>

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