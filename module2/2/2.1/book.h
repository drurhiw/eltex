#ifndef BOOK_H
#define BOOK_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define CAPACITY 10

typedef struct
{
    char last_name[MAX_STR];
    char first_name[MAX_STR];
    char phone_numbers[MAX_STR];
    char socials[MAX_STR];
} Contact;

typedef struct
{
    Contact* data;
    size_t size;
    size_t capacity;
} ContactList;

void initContact(ContactList* list, int capacity);
void freeList(ContactList* list);
void printContacts(ContactList* list);
void printError(ContactList* list);
void addContact(ContactList* list, Contact* c);
void deleteContact(ContactList* list, size_t index);
void editContact(ContactList* list, size_t index, const char* new_first, const char* new_last, const char* new_phone, const char* new_socials);


#endif //BOOK_H