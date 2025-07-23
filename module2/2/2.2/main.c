#include "calculator.h"
#include <stdio.h>

int main()
{
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

        double result = calculate(choice, count, numbers);  
        
        if (choice == 1)
        {
            printf("Сумма: %.2f\n", result);
        }
        else if (choice == 2)
        {
            printf("Разность: %.2f\n", result);
        }
        else if (choice == 3)
        {
            printf("Произведение: %.2f\n", result);
        }
        else if (choice == 4)
        {
            printf("Деление: %.2f\n", result);
        }
    }
    return 0;
}