#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

static void _exit_out_of_memory(void) {
  fprintf(stderr, "Out of memory.");
  exit(1);
}

struct node *node_new(int data) {
  struct node *node = malloc(sizeof(struct node));

  if (node == NULL) {
    _exit_out_of_memory();
  }

  node->data = data;
  node->next = NULL;

  return node;
}

struct singly_linked_list *singly_linked_list_new(void) {
  struct singly_linked_list *list = malloc(sizeof(struct singly_linked_list));

  if (list == NULL) {
    _exit_out_of_memory();
  }

  list->head = NULL;
  list->tail = NULL;

  return list;
}

struct node *singly_linked_list_get_head(struct singly_linked_list *list) {
  return list->head;
}

struct node *singly_linked_list_get_tail(struct singly_linked_list *list) {
  return list->tail;
}
