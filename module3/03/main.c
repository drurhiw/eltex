#include "book.h"

int main()
{
    ContactList book;
    initContact(&book, CAPACITY);
    loadContact(&book, "contacts.dat");
    
    while(1)
    {
        Contact c;
        char choice;
        printf("\nДобавить новый контакт, изменить, удалить, выйти (y/e/d/n): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');

        if (choice == 'n' || choice == 'N') {
            break;
        }

        if (choice == 'y' || choice == 'Y')
        {
            printf("Введите имя: ");
            scanf("%99s", c.first_name);

            printf("Введите фамилию: ");
            scanf("%99s", c.last_name);

            int ch;
            ch = getchar() != '\n';

            printf("Введите телефон (можно пропустить): ");
            fgets(c.phone_numbers, MAX_STR, stdin);
            c.phone_numbers[strlen(c.phone_numbers) - 1] = '\0';

            printf("Введите соцсети (можно пропустить): ");
            fgets(c.socials, MAX_STR, stdin);
            c.socials[strlen(c.socials)-1] = '\0';

            addContact(&book, &c);

            printContacts(&book);
        }

        if (choice == 'd' || choice == 'D')
        {
            int index;
            printf("Введите индекс контакта: ");
            scanf("%d", &index);
            if (index < 1 || index > book.size) 
            {
                printf("Ошибка: неверный номер контакта!\n");
                continue; 
            }
            deleteContact(&book, index - 1);
            printContacts(&book);
        } 
        
        if (choice == 'e' || choice == 'E')
        {
            int index;
            char new_first[MAX_STR] = "";
            char new_last[MAX_STR] = "";
            char new_phone[MAX_STR] = "";
            char new_socials[MAX_STR] = "";

            printf("Введите номер контакта для редактирования: ");
            scanf("%d", &index);

            if (index < 1 || index > book.size) 
            {
                printf("Ошибка: неверный номер контакта!\n");
                continue; 
            }

            int ch;
            ch = getchar() != '\n';

            printf("Новое имя: ");
            fgets(new_first, MAX_STR, stdin);
            new_first[strlen(new_first) - 1] = '\0';

            printf("Новая фамилия: ");
            fgets(new_last, MAX_STR, stdin);
            new_last[strlen(new_last) - 1] = '\0';

            printf("Новый телефон: ");
            fgets(new_phone, MAX_STR, stdin);
            new_phone[strlen(new_phone) - 1] = '\0';

            printf("Новые соцсети: ");
            fgets(new_socials, MAX_STR, stdin);
            new_socials[strlen(new_socials) - 1] = '\0';

            const char* first = NULL;
            const char* last = NULL;
            const char* phone = NULL;
            const char* social = NULL;

            if (strlen(new_first) > 0) first = new_first;
            if (strlen(new_last) > 0) last = new_last;
            if (strlen(new_phone) > 0) phone = new_phone;
            if (strlen(new_socials) > 0) social = new_socials;

            editContact(&book, index - 1, first, last, phone, social);
            printContacts(&book);
        }
        
    }

    saveContact(&book, "contacts.dat");
    freeList(&book);
    return 0;
}
