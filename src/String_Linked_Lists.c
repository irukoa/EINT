#include "String_Linked_Lists.h"

StringNode *createStringNode(char *string) {
  StringNode *newNode = (StringNode *)malloc(sizeof(StringNode));
  if (newNode == NULL) {
    fprintf(stderr, "Error allocating new node : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  newNode->string = strdup(string);
  if (newNode->string == NULL || strcmp(newNode->string, string) != 0) {
    fprintf(stderr, "Error allocating new node's string : %s\n",
            strerror(errno));
    exit(EXIT_FAILURE);
  }
  newNode->next = NULL;
  return newNode;
}

void addNodeAtEnd(StringNode **head,
                  char        *string) {
  StringNode *newNode = createStringNode(string);
  if (*head == NULL) {
    *head = newNode;
  } else {
    StringNode *temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void rmNodeAtBeggining(StringNode **head) {
  if (*head == NULL) {
    return;
  }
  StringNode *temp = *head;
  *head            = (*head)->next;
  free(temp->string);
  free(temp);
}

void freeList(StringNode **head) {
  while (*head != NULL) {
    rmNodeAtBeggining(head);
  }
}

char *sourceString(StringNode *head) {
  if (head == NULL) {
    return NULL;
  }
  char *string = strdup(head->string);
  if (string == NULL || strcmp(string, head->string) != 0) {
    fprintf(stderr, "Error sourcing node's string : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return string;
}
