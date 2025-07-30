#include <stdarg.h>

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