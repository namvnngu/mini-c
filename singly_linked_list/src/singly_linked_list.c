#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

static void _exit_out_of_memory(void) {
  fprintf(stderr, "Out of memory.");
  exit(1);
}

struct node *node_new(int data) {
  struct node *n = malloc(sizeof(struct node));

  if (n == NULL) {
    _exit_out_of_memory();
  }

  n->data = data;
  n->next = NULL;

  return n;
}

struct singly_linked_list *singly_linked_list_new(void) {
  struct singly_linked_list *l = malloc(sizeof(struct singly_linked_list));

  if (l == NULL) {
    _exit_out_of_memory();
  }

  l->head = NULL;

  return l;
}
