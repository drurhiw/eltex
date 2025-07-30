#include "chmod.h"

int main()
{
    while(true)
    {
        int choice;
        printf("Выберите режим:\n");
        printf("1. Ввод прав доступа вручную\n");
        printf("2. Чтение прав файла\n");
        printf("3. Модификация прав\n");
        printf("4. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            char input[16];
            printf("Введите строку: ");
            scanf("%15s", input);

            mode_t mode = parse_input(input);

            if (mode == 0) {
                printf("Некорректный ввод\n");
                return 1;
            }
            
            printf("Числовое представление: %o\n", mode);  
            printf("Битовое представление: 0x%04x\n", mode);
        }
        else if (choice == 2)
        {
            char filename[256];
            printf("Введите имя файла: ");
            scanf("%255s", filename);

            struct stat file_stat;
            if (stat(filename, &file_stat) == -1) {
                perror("Ошибка при получении информации о файле");
                continue;
            }

            mode_t mode = file_stat.st_mode & 0777;


            char symbolic[10] = "---------";

            if (mode & S_IRUSR)
            {
                symbolic[0] = 'r';
            }
            else 
            {
                symbolic[0] = '-';
            }

            if (mode & S_IWUSR)
            {
                symbolic[1] = 'w';
            }
            else 
            {
                symbolic[1] = '-';
            }

            if (mode & S_IXUSR)
            {
                symbolic[2] = 'x';
            }
            else 
            {
                symbolic[2] = '-';
            }

            if (mode & S_IRGRP)
            {
                symbolic[3] = 'r';
            }
            else 
            {
                symbolic[3] = '-';
            }

            if (mode & S_IWGRP)
            {
                symbolic[4] = 'w';
            }
            else 
            {
                symbolic[4] = '-';
            }

            if (mode & S_IXGRP)
            {
                symbolic[5] = 'x';
            }
            else 
            {
                symbolic[5] = '-';
            }

            if (mode & S_IROTH)
            {
                symbolic[6] = 'r';
            }
            else 
            {
                symbolic[6] = '-';
            }

            if (mode & S_IWOTH)
            {
                symbolic[7] = 'w';
            }
            else 
            {
                symbolic[7] = '-';
            }

            if (mode & S_IXOTH)
            {
                symbolic[8] = 'x';
            }
            else 
            {
                symbolic[8] = '-';
            }
            
            symbolic[9] = '\0';

            printf("Буквенное представление: %s\n", symbolic);
            printf("Числовое представление: %o\n", mode);
            printf("Битовое представление: 0x%04x\n", mode);
        }
        else if (choice == 3)
        {
            char input[16];
            printf("Введите текущие права (символьные или восьмеричные): ");
            scanf("%15s", input);

            mode_t mode = parse_input(input);
            if (mode == 0) {
                printf("Некорректный ввод прав\n");
                continue;
            }

            char mod[16];
            printf("Введите модификацию (например, u+x, g-w, a=r): ");
            scanf("%15s", mod);

            mode = modify_mode(mode, mod);

            // вывод
            char symbolic[10] = "---------";
            if (mode & S_IRUSR)
            {
                symbolic[0] = 'r';
            }
            else
            {
                symbolic[0] = '-';
            }

            if (mode & S_IWUSR)
            {
                symbolic[1] = 'w';
            }
            else
            {
                symbolic[1] = '-';
            }

            if (mode & S_IXUSR)
            {
                symbolic[2] = 'x';
            }
            else
            {
                symbolic[2] = '-';
            }
 
            if (mode & S_IRGRP)
            {
                symbolic[3] = 'r';
            }
            else
            {
                symbolic[3] = '-';
            }

            if (mode & S_IWGRP)
            {
                symbolic[4] = 'w';
            }
            else
            {
                symbolic[4] = '-';
            }

            if (mode & S_IXGRP)
            {
                symbolic[5] = 'x';
            }
            else
            {
                symbolic[5] = '-';
            }

            if (mode & S_IROTH)
            {
                symbolic[6] = 'r';
            }
            else
            {
                symbolic[6] = '-';
            }

            if (mode & S_IWOTH)
            {
                symbolic[7] = 'w';
            }
            else
            {
                symbolic[7] = '-';
            }

            if (mode & S_IXOTH)
            {
                symbolic[8] = 'x';
            }
            else
            {
                symbolic[8] = '-';
            }

            symbolic[9] = '\0';

            printf("Буквенное представление: %s\n", symbolic);
            printf("Числовое представление: %o\n", mode);
            printf("Битовое представление: 0x%04x\n", mode);
        }
        else if (choice == 4) 
        {
            break;
        } 
        else 
        {
            printf("Неверный ввод, попробуйте снова.\n");
        }
    }
    

    return 0;
}