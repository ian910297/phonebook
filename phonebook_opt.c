#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

#if OPT==1
entry *init()
{
    entry *new_node;

    new_node = (entry*)malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    new_node->pNext = NULL;

    return new_node;
}

entry *findName(char lastName[], entry *pHead)
{
    /* TODO: implement */
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

void release_memory(entry *e)
{
    entry *tmp;

    while (e!=NULL) {
        tmp = e;
        e = e->pNext;
        free(tmp);
    }
}
#elif OPT==2
entry *init()
{
    return append("Ian Chi", NULL);
}

entry *findName(char lastName[], entry *pHead)
{
    int result;
    while (pHead!=NULL) {
        result = strcmp(lastName, pHead->lastName);

        if (result==0) {
            printf("Find %s\n", pHead->lastName);
            return pHead;
        } else if (result>0) {
            pHead = pHead->pLeft;
        } else {
            pHead = pHead->pRight;
        }
    }

    return NULL;
}

entry *append(char lastName[], entry *root)
{
    entry *new_node;
    entry *current;
    entry *parent;

    // build new_node
    new_node = (entry*)malloc(sizeof(entry));
    strcpy(new_node->lastName, lastName);
    new_node->pLeft = NULL;
    new_node->pRight = NULL;
    if (root==NULL) {
        return new_node;
    } else {
        // find the leaf
        current = root;
        while (current!=NULL) {
            parent = current;
            if (strcmp(lastName, current->lastName) > 0) {
                current = current->pLeft;
            } else {
                current = current->pRight;
            }
        }

        // insert the new_node
        if (strcmp(lastName, parent->lastName) > 0) {
            parent->pLeft = new_node;
        } else {
            parent->pRight = new_node;
        }
    }

    return root;
}

void release_memory(entry *e)
{
    if (e!=NULL) {
        release_memory(e->pLeft);
        release_memory(e->pRight);
    }

    free(e);
}
#endif
