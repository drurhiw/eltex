#include "task.h"

IpAddress parseId (const char *str, int *error)
{
    IpAddress ip = {0, 0, 0, 0};
    int values[4];

    if (sscanf(str, "%d.%d.%d.%d", &values[0], &values[1], &values[2], &values[3]) != 4)
    {
        *error = 1;
        return ip;
    }

    for (int i = 0; i < 4; i++)
    {
        if (values[i] < 0 || values[i] > 255)
        {
            *error = 1;
            return ip;
        }
    }

    ip.o1 = (unsigned char)values[0]; 
    ip.o2 = (unsigned char)values[1];
    ip.o3 = (unsigned char)values[2];
    ip.o4 = (unsigned char)values[3];

    *error = 0;

    return ip;
} 

unsigned int pt_uint32(IpAddress ip)
{
    return (ip.o1 << 24) | (ip.o2 << 16) | (ip.o3 << 8) | ip.o4;
}

IpAddress randomIP()
{
    IpAddress ip;
    ip.o1 = rand() % 256;
    ip.o2 = rand() % 256;
    ip.o3 = rand() % 256;
    ip.o4 = rand() % 256;
    return ip;
}

int same_subnet(IpAddress ip1, IpAddress ip2, IpAddress mask) 
{
    unsigned int a = pt_uint32(ip1);
    unsigned int b = pt_uint32(ip2);
    unsigned int m = pt_uint32(mask);
    return (a & m) == (b & m);
}