#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <stdbool.h>

struct node {
  int val;
  struct Node *next;
};

struct linked_list {
  struct node *head;
  struct node *tail;
};

struct node *node_new(int val);

struct linked_list *linked_list_new(void);
struct node *linked_list_get_head(struct linked_list *list);
struct node *linked_list_get_tail(struct linked_list *list);
void linked_list_insert_head(struct linked_list *list, struct node *node);
void linked_list_insert_tail(struct linked_list *list, struct node *node);
void linked_list_remove_head(struct linked_list *list);
void linked_list_remove_tail(struct linked_list *list);
void linked_list_traverse(struct linked_list *list);
void linked_list_foreach(struct linked_list *list, void (*func)(struct node *));
bool linked_list_contain(struct linked_list *list, struct node *node);
void linked_list_clear(struct linked_list *list);
void linked_list_delete(struct linked_list *list);

#endif /* _LINKED_LIST */
