#ifndef _SINGLY_LINKED_LIST
#define _SINGLY_LINKED_LIST

#include <stdbool.h>

struct node {
  int data;
  struct Node *next;
};

struct singly_linked_list {
  struct node *head;
};

struct node *node_new(int val);

struct singly_linked_list *singly_linked_list_new(void);

#endif /* _SINGLY_LINKED_LIST */
