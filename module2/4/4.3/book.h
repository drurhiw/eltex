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
    struct ContactNode* left;
    struct ContactNode* right;
} ContactNode;

typedef struct 
{
    ContactNode* root;
    size_t size;
} ContactTree;

void initContact(ContactTree* tree);
void freeNode(ContactNode* node);
void printContacts(ContactList* list);
void printError(ContactList* list);

ContactNode* createNode(Contact c);

void addContact(ContactList* list, Contact* c);
void deleteContact(ContactList* list, size_t index);
void editContact(ContactList* list, size_t index, const char* new_first, const char* new_last, const char* new_phone, const char* new_socials);


#endif //BOOK_H