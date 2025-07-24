#include "book.h"

int main()
{
    ContactTree book;
    initContact(&book);
    
    while(1)
    {
        Contact c;
        char choice;
        printf("\nДобавить новый контакт, изменить, удалить, выйти (y/e/d/n): ");
        scanf(" %c", &choice);

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

            printTreeWrapper(&book);
        }

        if (choice == 'd' || choice == 'D')
        {
            Contact c;
            printf("Введите фамилию контакта: ");
            scanf("%99s", c.last_name);

            book.root = deleteContact(book.root, c.last_name);

            if (book.root == NULL)
                book.size = 0;
            else
                book.size--;
            printTreeWrapper(&book);
        } 
        
        if (choice == 'e' || choice == 'E')
        {
            char old_last_name[MAX_STR];
            char buf[MAX_STR];
            Contact *original = NULL;
            Contact updated;

            printf("Введите фамилию контакта для редактирования: \n");
            scanf("%99s", old_last_name);

            int c;
            while ((c = getchar()) != '\n') { } 


            ContactNode* node = findNode(book.root, old_last_name);
            if (!node) {
                printf("Контакт не найден.\n");
                continue;
            }

            updated = *(node->data);

            printf("Новое имя: \n");
            if (fgets(buf, MAX_STR, stdin)) 
            {
                buf[strcspn(buf, "\n")] = '\0';
                if (strlen(buf) > 0) 
                {
                    strncpy(updated.first_name, buf, MAX_STR);
                }
            }
        
            printf("Новая фамилия: \n");
            if (fgets(buf, MAX_STR, stdin)) 
            {
                buf[strcspn(buf, "\n")] = '\0';
                if (strlen(buf) > 0) 
                {
                    strncpy(updated.last_name, buf, MAX_STR);
                }
            }
        
            printf("Новый телефон: \n");
            if (fgets(buf, MAX_STR, stdin)) 
            {
                buf[strcspn(buf, "\n")] = '\0';
                if (strlen(buf) > 0) 
                {
                    strncpy(updated.phone_numbers, buf, MAX_STR);
                }
            }
        
            printf("Новые соцсети: \n");
            if (fgets(buf, MAX_STR, stdin)) 
            {
                buf[strcspn(buf, "\n")] = '\0';
                if (strlen(buf) > 0) 
                {
                    strncpy(updated.socials, buf, MAX_STR);
                }
            }

            editContact(&book, old_last_name, &updated);
            printTreeWrapper(&book);
        }
        
    }


    freeNode(book.root);
    return 0;
}
