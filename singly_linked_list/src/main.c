#include "singly_linked_list.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct singly_linked_list *ll = singly_linked_list_new();

  printf("insert heads\n");
  for (int i = 5; i >= 1; i--)
    singly_linked_list_insert_head(ll, node_new(i));
  singly_linked_list_traverse(ll);
  printf("\n\n");

  printf("insert tails\n");
  for (int i = 6; i <= 10; i++)
    singly_linked_list_insert_tail(ll, node_new(i));
  singly_linked_list_traverse(ll);
  printf("\n\n");

  printf("remove head\n");
  singly_linked_list_remove_head(ll);
  singly_linked_list_traverse(ll);
  printf("\n\n");

  printf("remove tail\n");
  singly_linked_list_remove_tail(ll);
  singly_linked_list_traverse(ll);
  printf("\n\n");
}
