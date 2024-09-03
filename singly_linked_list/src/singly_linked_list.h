#ifndef _SINGLY_LINKED_LIST
#define _SINGLY_LINKED_LIST

#include <stdbool.h>

struct node {
  int data;
  struct node *next;
};

struct singly_linked_list {
  struct node *head;
  struct node *tail;
};

struct node *node_new(int val);

struct singly_linked_list *singly_linked_list_new(void);
struct node *singly_linked_list_get_head(struct singly_linked_list *list);
struct node *singly_linked_list_get_tail(struct singly_linked_list *list);
void singly_linked_list_insert_head(struct singly_linked_list *list,
                                    struct node *node);
void singly_linked_list_insert_tail(struct singly_linked_list *list,
                                    struct node *node);
void singly_linked_list_remove_head(struct singly_linked_list *list);
void singly_linked_list_remove_tail(struct singly_linked_list *list);
void singly_linked_list_traverse(struct singly_linked_list *list);
void singly_linked_list_foreach(struct singly_linked_list *list,
                                void (*func)(struct node *));
bool singly_linked_list_contain(struct singly_linked_list *list,
                                struct node *node);
void singly_linked_list_clear(struct singly_linked_list *list);
void singly_linked_list_delete(struct singly_linked_list *list);

#endif /* _SINGLY_LINKED_LIST */
