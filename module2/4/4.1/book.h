#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct Contact 
{
    char first_name[MAX_STR];
    char last_name[MAX_STR];
    char phone_numbers[MAX_STR];
    char socials[MAX_STR];
} Contact;


typedef struct ContactNode
{
    Contact data;
    struct ContactNode* prev; //Указатель на предыдущий элемент
    struct ContactNode* next; //Указатель на следующий элемент
} ContactNode;

typedef struct ContactList
{
    ContactNode* head; //Указатель на голову 
    ContactNode* tail; //Указатель на хвост
} ContactList;

void initContact(ContactList* list);
void freeList(ContactList* list);
void printContacts(ContactList* list);
void addContact(ContactList* list, Contact* c);
void deleteContact(ContactList* list, size_t index);
void editContact(ContactList* list, size_t index, const char* new_first, const char* new_last, const char* new_phone, const char* new_socials);


#endif //BOOK_H