#ifndef CALCULATOR2_H
#define CALCULATOR2_H


#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

typedef double (*func)(int, ...);
extern func operations[];

#endif //CALCULATOR2_H