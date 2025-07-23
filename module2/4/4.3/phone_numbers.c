#include "book.h"

void initContact(ContactTree* tree)
{
    tree->root = NULL;
    tree->size = 0;
}

void freeNode(ContactNode* node) 
{
    if (!node) return;
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

void printContacts(ContactList* list) 
{
    if ((*list).size == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    printf("\nСписок контактов:\n");
    for (size_t i = 0; i < (*list).size; i++) {
        printf("%zu. %s %s\n", i + 1, (*list).data[i].first_name, (*list).data[i].last_name);

        if (strlen((*list).data[i].phone_numbers) > 0)
            printf("   Телефон: %s\n", (*list).data[i].phone_numbers);
        else
            printf("   Телефон: [не указан]\n");

        if (strlen((*list).data[i].socials) > 0)
            printf("   Соцсети: %s\n", (*list).data[i].socials);
        else
            printf("   Соцсети: [не указаны]\n");
    }
}

void printError(ContactList* list)
{
    printf("Список заполнен, нельзя добавить контакт.\n");
    printContacts(list);
}

ContactNode* createNode(Contact c)
{
    ContactNode* node = malloc(sizeof(ContactNode));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ContactNode* insertNode(ContactNode* root, Contact c, int* insert)
{
    
}

void addContact(ContactList* list, Contact* c)
{
    ContactList l = *list;
    if (l.size < l.capacity)
    {
        l.data[l.size] = *c;
        l.size++;
        *list = l;
    } 
    else
    {
        printError(list);
        exit(1);
    }
}

void editContact(ContactList* list, size_t index, const char* new_first, const char* new_last, const char* new_phone, const char* new_socials)
{
    if ((*list).size == 0 || index >= (*list).size)
    {
        return;
    }

    Contact* c = &(*list).data[index];

    if (new_first !=  NULL && strlen(new_first) > 0)
    {
        strncpy((*c).first_name, new_first, MAX_STR);
    }

    if (new_last !=  NULL && strlen(new_last) > 0)
    {
        strncpy((*c).last_name, new_last, MAX_STR);
    }

    if (new_phone !=  NULL && strlen(new_phone) > 0)
    {
        strncpy((*c).phone_numbers, new_phone, MAX_STR);
    }

    if (new_socials !=  NULL && strlen(new_socials) > 0)
    {
        strncpy((*c).socials, new_socials, MAX_STR);
    }
}


void deleteContact(ContactList* list, size_t index)
{
    size_t size = (*list).size;

    if (size == 0)
    {
        return;
    }
    else if (index >= size)
    {
        return;
    }

    size_t i = index;
    while (i < size - 1)
    {
        (*list).data[i] = (*list).data[i + 1];
        i++;
    }

    (*list).size = size - 1;

}


