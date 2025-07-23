#include "calculator2.h"

int main()
{
    func operations[] = { sum, sub, mul, divide };
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
    return 0;
}