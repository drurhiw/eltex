#ifndef CALCULATOR2_H
#define CALCULATOR2_H


#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

typedef double (*func)(int, ...);

double sum(int n, ...);
double sub(int n, ...);
double mul(int n, ...);
double divide(int n, ...);


#endif //CALCULATOR2_H