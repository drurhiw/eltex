#include "calculator.h"

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

double calculate(int choice, int count, double numbers[])
{
    switch(count)
    {
        case 1: return numbers[0];
        case 2: 
            if (choice == 1) return sum(2, numbers[0], numbers[1]);
            else if (choice == 2) return sub(2, numbers[0], numbers[1]);
            else if (choice == 3) return mul(2, numbers[0], numbers[1]);
            else return divide(2, numbers[0], numbers[1]);
        case 3: 
            if (choice == 1) return sum(3, numbers[0], numbers[1], numbers[2]);
            else if (choice == 2) return sub(3, numbers[0], numbers[1], numbers[2]);
            else if (choice == 3) return mul(3, numbers[0], numbers[1], numbers[2]);
            else return divide(3, numbers[0], numbers[1], numbers[2]);
        case 4: 
            if (choice == 1) return sum(4, numbers[0], numbers[1], numbers[2], numbers[3]);
            else if (choice == 2) return sub(4, numbers[0], numbers[1], numbers[2], numbers[3]);
            else if (choice == 3) return mul(4, numbers[0], numbers[1], numbers[2], numbers[3]);
            else return divide(4, numbers[0], numbers[1], numbers[2], numbers[3]);
        default: return 0;
    }
}
