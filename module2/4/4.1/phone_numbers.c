#include "book.h"

//Упорядоченно по фамилии

void initContact(ContactList* list)
{
    (*list).head = NULL;
    (*list).tail = NULL;
}

void freeList(ContactList* list) {
    ContactNode* current = (*list).head;
    while (current) {
        ContactNode* next = (*current).next;
        free(current);
        current = next;
    }
    (*list).head = NULL;
    (*list).tail = NULL;
}


void printContacts(ContactList* list) 
{
    ContactNode* current = (*list).head;
    size_t i = 1;

    if (!current) 
    {
        printf("Телефонная книга пуста.\n");
        return;
    }

    printf("\nСписок контактов:\n");
    while(current)
    {
        printf("%zu. %s %s\n", i, (*current).data.first_name, (*current).data.last_name);

        if (strlen((*current).data.phone_numbers) > 0)
            printf("   Телефон: %s\n", (*current).data.phone_numbers);
        else
            printf("   Телефон: [не указан]\n");

        if (strlen((*current).data.socials) > 0)
            printf("   Соцсети: %s\n", (*current).data.socials);
        else
            printf("   Соцсети: [не указаны]\n");

        current = (*current).next;
        ++i;
    }
}

void addContact(ContactList* list, Contact* c)
{
    ContactNode* newNode = malloc(sizeof(ContactNode));
    (*newNode).data = *c;
    (*newNode).prev = NULL;
    (*newNode).next = NULL;
    
    ContactNode* current = (*list).head;

    while(current)
    {
        char* new_last = (*c).last_name;
        char* now_last = (*current).data.last_name;
        int result = strcmp(new_last, now_last);

        if (result <= 0)
        {
            break;
        }

        current = (*current).next;
    }

    if (current == NULL)
    {
        if ((*list).tail == NULL)
        {
            (*list).head = newNode;
            (*list).tail = newNode;
        }
        else 
        {
            (*newNode).prev = (*list).tail;
            (*(*list).tail).next = newNode;
            (*list).tail = newNode;
        }
    }
    else 
    {
        (*newNode).next = current;
        (*newNode).prev = (*current).prev;

        if ((*current).prev != NULL)
        {
            (*(*current).prev).next = newNode;
        }
        else
        {
            (*list).head = newNode;
        }
        (*current).prev = newNode;
    }
}

void editContact(ContactList* list, size_t index, const char* new_first, const char* new_last, const char* new_phone, const char* new_socials) 
{
    ContactNode* current = (*list).head;
    size_t i = 0;
    while (current && i < index) {
        current = (*current).next;
        ++i;
    }

    if (!current) return;

    Contact updated = (*current).data;

    if (new_first && strlen(new_first) > 0)
        strncpy(updated.first_name, new_first, MAX_STR - 1);

    if (new_last && strlen(new_last) > 0)
        strncpy(updated.last_name, new_last, MAX_STR - 1);

    if (new_phone && strlen(new_phone) > 0)
        strncpy(updated.phone_numbers, new_phone, MAX_STR - 1);

    if (new_socials && strlen(new_socials) > 0)
        strncpy(updated.socials, new_socials, MAX_STR - 1);

    if ((*current).prev)
    {
        (*(*current).prev).next = (*current).next;
    }
    else 
    {
        (*list).head = (*current).next;
    }

    if ((*current).next)
    {
        (*(*current).next).prev = (*current).prev;
    }
    else 
    {
        (*list).tail = (*current).prev;
    }

    free(current);

    addContact(list, &updated);
}


void deleteContact(ContactList* list, size_t index)
{
    ContactNode* current = (*list).head;
    size_t i = 0;

    while (current && i < index)
    {
        current = (*current).next;
        ++i;
    }

    if ((*current).prev)
    {
        (*(*current).prev).next = (*current).next;
    }
    else
    {
        (*list).head = (*current).next;
    }

    if ((*current).next)
    {
        (*(*current).next).prev = (*current).prev;
    }
    else 
    {
        (*list).tail = (*current).prev;
    }

    free(current);
}


