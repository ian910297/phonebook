#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 32

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1

#if OPT==1
/*
 * Simplify data structure
 */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);
#elif OPT==2
/*
 * add binary search tree
 */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pLeft;
    struct __PHONE_BOOK_ENTRY *pRight;
} entry;

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);
#endif

#endif
