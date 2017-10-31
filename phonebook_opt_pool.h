#pragma once
#define MAX_LAST_NAME_SIZE 32

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 2

#include "pool.h"

#if OPT==1
/*
 * Simplify data structure
 */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;
#elif OPT==2
/*  
 *  Binary search tree
 */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pLeft;
    struct __PHONE_BOOK_ENTRY *pRight;
} entry;
#endif

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e, MEMPool *pool);
entry *init(MEMPool *pool);
void release_memory(entry *e);
