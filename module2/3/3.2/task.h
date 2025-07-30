#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    unsigned char o1, o2, o3, o4;
} IpAddress;

IpAddress parseId (const char *str, int *error);
unsigned int pt_uint32(IpAddress ip);
IpAddress randomIP();
int same_subnet(IpAddress ip1, IpAddress ip2, IpAddress mask);

#endif //TASK_H