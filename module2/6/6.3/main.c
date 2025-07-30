#include "calculator2.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

#define MAX_FUNCS 10

func operations[MAX_FUNCS];

int main()
{
    void* handle = dlopen("./libcalc.so", RTLD_LAZY);
    
    dlerror();

    operations[0] = (func)dlsym(handle, "sum");
    operations[1] = (func)dlsym(handle, "sub");
    operations[2] = (func)dlsym(handle, "mul");
    operations[3] = (func)dlsym(handle, "divide");

    char* err = dlerror();


    while(true)
    {
        int choice;
        int count;
        printf("1. Сумма\n");
        printf("2. Разность\n");
        printf("3. Произведение\n");
        printf("4. Деление\n");
        printf("5. Выход\n");
        printf("Введите опцию: \n");
        scanf("%d", &choice);

        if (choice < 1 || choice > 5)
        {
            printf("Введите правильную опцию.\n");
            continue;
        }

        if (choice == 5)
        {
            break;
        }

        printf("Введите количество чисел не больше 4: \n");
        scanf("%d", &count);
        if (count > 4)
        {
            printf("Количество чисел не должно превышать 4\n");
            continue;
        }

        if (count == 0)
        {
            printf("Ошибка: количество чисел не может быть 0!\n");
            continue;
        }

        double numbers[4]; 
        printf("Введите %d числа (через пробел): ", count);
        for (int i = 0; i < count; i++) {
            scanf("%lf", &numbers[i]);
        }

        double result = 0;  
        
        switch (count)
        {
            case 1:
                result = operations[choice - 1](1, numbers[0]);
                break;
            case 2:
                result = operations[choice - 1](2, numbers[0], numbers[1]);
                break;
            case 3:
                result = operations[choice - 1](3, numbers[0], numbers[1], numbers[2]);
                break;
            case 4:
                result = operations[choice - 1](4, numbers[0], numbers[1], numbers[2], numbers[3]);
                break;
        }
        printf("Результат: %.2f\n", result);
    }
    dlclose(handle);
    return 0;
}