#include "String_Linked_Lists.h"

void String_Linked_Lists_check_remove_from_empty_list() {

  StringNode *string_list = NULL;

  rmNodeAtBeggining(&string_list);

  assert(string_list == NULL);
  fprintf(stderr, ">>Test OK\n");
}

void String_Linked_Lists_check_freeList() {

  StringNode *string_list = NULL;

  char *str1 = "string1";
  char *str2 = "string2";
  char *str3 = "string1";
  char *str4 = "string2";
  char *str5 = "string1";
  addNodeAtEnd(&string_list, str1);
  addNodeAtEnd(&string_list, str2);
  addNodeAtEnd(&string_list, str3);
  addNodeAtEnd(&string_list, str4);
  addNodeAtEnd(&string_list, str5);

  freeList(&string_list);

  assert(string_list == NULL);
  fprintf(stderr, ">>Test OK\n");
}

void String_Linked_Lists_check_source_string() {

  StringNode *string_list = NULL;

  char *str1 = "string1";
  char *str2 = "string2";
  addNodeAtEnd(&string_list, str1);
  addNodeAtEnd(&string_list, str2);

  char *s1 = sourceString(string_list);
  assert(strcmp(s1, str1) == 0);
  rmNodeAtBeggining(&string_list);
  free(s1);

  char *s2 = sourceString(string_list);
  assert(strcmp(s2, str2) == 0);
  rmNodeAtBeggining(&string_list);
  free(s2);

  char *s3 = sourceString(string_list);
  assert(s3 == NULL);
  free(s3);

  freeList(&string_list);

  assert(string_list == NULL);
  fprintf(stderr, ">>Test OK\n");
}
