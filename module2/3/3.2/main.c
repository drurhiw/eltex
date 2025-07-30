#include "task.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        return 1;
    }

    srand(time(NULL));

    int err;
    IpAddress gateway = parseId(argv[1], &err);
    if (err)
    {
        return 1;
    }

    IpAddress mask = parseId(argv[2], &err);
    if (err)
    {
        return 1;
    }

    int count = atoi(argv[3]);
    if (count <= 0) {
        return 1;
    }

    int same = 0;

    for (int i = 0; i < count; i++) {
        IpAddress dest = randomIP();

        printf("Пакет %2d: %u.%u.%u.%u -> ", i + 1, dest.o1, dest.o2, dest.o3, dest.o4);

        if (same_subnet(dest, gateway, mask)) {
            printf("своя подсеть \n");
            same++;
        } else {
            printf("другая подсеть \n");
        }
    }

    printf("\nИтоги:\n");
    printf("Своей подсети: %d пакетов (%.2f%%)\n", same, 100.0 * same / count);
    printf("Других сетей: %d пакетов (%.2f%%)\n", count - same, 100.0 * (count - same) / count);

    return 0;
}