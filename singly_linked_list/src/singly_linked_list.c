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

  if (node == NULL)
    _exit_out_of_memory();

  node->data = data;
  node->next = NULL;

  return node;
}

struct singly_linked_list *singly_linked_list_new(void) {
  struct singly_linked_list *list = malloc(sizeof(struct singly_linked_list));

  if (list == NULL)
    _exit_out_of_memory();

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

void singly_linked_list_insert_head(struct singly_linked_list *list,
                                    struct node *node) {
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    node->next = list->head;
    list->head = node;
  }
}

void singly_linked_list_insert_tail(struct singly_linked_list *list,
                                    struct node *node) {
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}

void singly_linked_list_remove_head(struct singly_linked_list *list) {
  if (list->head == NULL)
    return;

  struct node *head = list->head;
  list->head = head->next;
  head->next = NULL;
  free(head);
}

void singly_linked_list_remove_tail(struct singly_linked_list *list) {
  if (list->head == NULL)
    return;

  struct node *penultimate = NULL;

  for (struct node *current = list->head; current; current = current->next)
    penultimate = current;

  struct node *tail = list->tail;
  penultimate->next = NULL;
  list->tail = penultimate;
  free(tail);
}

void singly_linked_list_traverse(struct singly_linked_list *list) {
  for (struct node *current = list->head; current; current = current->next)
    if (current->next != NULL)
      printf("%d -> ", current->data);
    else
      printf("%d", current->data);
}

void singly_linked_list_foreach(struct singly_linked_list *list,
                                void (*func)(struct node *)) {
  for (struct node *current = list->head; current; current = current->next)
    func(current);
}

bool singly_linked_list_contain(struct singly_linked_list *list,
                                struct node *node) {
  for (struct node *current = list->head; current; current = current->next)
    if (current->data == node->data)
      return true;

  return false;
}

void singly_linked_list_clear(struct singly_linked_list *list) {
  if (list->head == NULL)
    return;

  struct node *current = list->head;
  do {
    struct node *cleared_node = current;
    current = current->next;
    free(current);
  } while (current != NULL);

  list->head = NULL;
  list->tail = NULL;
}

void singly_linked_list_delete(struct singly_linked_list *list) {
  singly_linked_list_clear(list);
  free(list);
}
