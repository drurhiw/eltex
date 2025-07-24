#ifndef BOOK_H
#define BOOK_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct
{
    char last_name[MAX_STR];
    char first_name[MAX_STR];
    char phone_numbers[MAX_STR];
    char socials[MAX_STR];
} Contact;

typedef struct ContactNode
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
void printError(ContactTree* tree);

void printTree(ContactNode* node, int level);
void printTreeWrapper(ContactTree* tree);
void printContactsRecursive(ContactNode* node, int* count);
void printContacts(ContactTree* tree);

ContactNode* createNode(Contact c);
ContactNode* insertNode(ContactNode* root, Contact c, int* insert);

void addContact(ContactTree* tree, Contact* c);
ContactNode* findMinNode(ContactNode* node);
ContactNode* deleteContact(ContactNode* root, const char* last_name);
void editContact(ContactTree* tree, const char* old_last_name, Contact* updated_contact);
ContactNode* findNode(ContactNode* root, const char* last_name);

#endif //BOOK_H