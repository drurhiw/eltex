#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>


double sum(int n, ...);
double sub(int n, ...);
double mul(int n, ...);
double divide(int n, ...);
double calculate(int choice, int count, double numbers[]);


#endif //CALCULATOR_H