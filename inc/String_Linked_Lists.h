#ifndef STRING_LINKED_LISTS
#define STRING_LINKED_LISTS

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of string-storing linked list node and its constructor.
typedef struct _StringNode {
  char               *string;
  struct _StringNode *next;
} StringNode;
StringNode *createStringNode(char *string);

// Functions which modify the queue-like linked list.

void addNodeAtEnd(StringNode **head,
                  char        *string);

void rmNodeAtBeggining(StringNode **head);

void freeList(StringNode **head);

// Functions which only read the linked list.

char *sourceString(StringNode *head);

#endif
