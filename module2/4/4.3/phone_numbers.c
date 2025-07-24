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
    free(node->data);
    free(node);
}

void printTree(ContactNode* node, int level) 
{
    if (!node) return;

    printTree(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("    ");  
    }
    printf("%s %s\n", node->data->last_name, node->data->first_name);

    printTree(node->left, level + 1);
}

void printTreeWrapper(ContactTree* tree)
{
    if (tree->root == NULL) {
        printf("Телефонная книга пуста.\n");
        return;
    }
    printTree(tree->root, 0);
}

void printContactsRecursive(ContactNode* node, int* count) {
    if (!node) return;

    printContactsRecursive(node->left, count);

    printf("%d. %s %s\n", (*count) + 1, node->data->first_name, node->data->last_name);

    if (strlen(node->data->phone_numbers) > 0)
        printf("   Телефон: %s\n", node->data->phone_numbers);
    else
        printf("   Телефон: [не указан]\n");

    if (strlen(node->data->socials) > 0)
        printf("   Соцсети: %s\n", node->data->socials);
    else
        printf("   Соцсети: [не указаны]\n");

    (*count)++;

    printContactsRecursive(node->right, count);
}

void printContacts(ContactTree* tree) {
    if (!tree || tree->root == NULL) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    printf("\nСписок контактов:\n");
    int count = 0;
    printContactsRecursive(tree->root, &count);
}


void printError(ContactTree* tree)
{
    printf("Список заполнен, нельзя добавить контакт.\n");
    printContacts(tree);
}

ContactNode* createNode(Contact c)
{
    ContactNode* node = malloc(sizeof(ContactNode));
    node->data = malloc(sizeof(Contact));  
    if (!node->data) {
        free(node);
        return NULL;
    }

    *(node->data) = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ContactNode* insertNode(ContactNode* root, Contact c, int* insert)
{
    if (root == NULL)
    {
        *insert = 1;
        return createNode(c);;
    }

    int cmp = strcmp(c.last_name, root->data->last_name);
    if (cmp < 0)
    {
        root->left = insertNode(root->left, c, insert);
    }
    else if (cmp > 0)
    {
        root->right = insertNode(root->right, c, insert);
    }
    else 
    {
        *insert = 0;
    }
    return root;
}

void addContact(ContactTree* tree, Contact* c)
{
    int inserted = 0;
    tree->root = insertNode(tree->root, *c, &inserted);
    if (inserted)
    {
        tree->size++;
    }
    else
    {
        printError(tree);
    }
}

void editContact(ContactTree* tree, const char* old_last_name, Contact* updated_contact)
{
    ContactNode* node = findNode(tree->root, old_last_name);
    if (!node)
    {
        return;
    }

    tree->root = deleteContact(tree->root, old_last_name);
    tree->size--;

    addContact(tree, updated_contact);
}

ContactNode* findNode(ContactNode* root, const char* last_name)
{
    if (root == NULL) return NULL;

    int cmp = strcmp(last_name, root->data->last_name);

    if (cmp == 0) {
        return root;  
    } else if (cmp < 0) {
        return findNode(root->left, last_name);
    } else {
        return findNode(root->right, last_name);
    }
}


ContactNode* findMinNode(ContactNode* node)
{
    while (node && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

ContactNode* deleteContact(ContactNode* root, const char* last_name)
{
    if (root == NULL)
    {
        return NULL;
    }

    int cmp = strcmp(last_name, root->data->last_name);

    if (cmp < 0)
    {
        root->left = deleteContact(root->left, last_name);
    }
    else if (cmp > 0)
    {
        root->right = deleteContact(root->right, last_name);
    }
    else 
    {
        //Если потомков нет
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        //Если только правый потомок
        else if (root->left == NULL)
        {
            ContactNode* temp = root->right;
            free(root);
            return temp;
        }

        //Если только левый потомок
        else if (root->right == NULL)
        {
            ContactNode* temp = root->left;
            free(root);
            return temp;
        }

        //Если два потомка
        else 
        {
            ContactNode* minRight = findMinNode(root->right);
            *(root->data) = *(minRight->data);
            root->right = deleteContact(root->right, minRight->data->last_name);
        }
    }
    return root;

}


