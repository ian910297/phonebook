#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

entry *init()
{
    entry *new_node;

    new_node = (entry*)malloc(sizeof(new_node));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    new_node->pNext = NULL;

    return new_node;
}

/* original version */
entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
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
