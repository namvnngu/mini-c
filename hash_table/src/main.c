#include <stdio.h>

#include "ht.h"

int main(int argc, char *argv[]) {
  struct ht *ht = ht_new();

  printf("hash table size: %d\n", ht->size);

  printf("before:\n");

  htpair_insert(ht, "name", "John");
  htpair_insert(ht, "age", "18");
  htpair_insert(ht, "phone", "0123456789");
  printf("name: %s\n", htpair_get_value(ht, "name"));
  printf("age: %s\n", htpair_get_value(ht, "age"));
  printf("phone: %s\n", htpair_get_value(ht, "phone"));
  printf("hash table size: %d\n", ht->size);

  printf("after:\n");

  htpair_insert(ht, "name", "Leo");
  htpair_insert(ht, "age", "19");
  htpair_delete(ht, "phone");
  printf("name: %s\n", htpair_get_value(ht, "name"));
  printf("age: %s\n", htpair_get_value(ht, "age"));
  printf("phone: %s\n", htpair_get_value(ht, "phone"));
  printf("hash table size: %d\n", ht->size);

  ht_delete(ht);
}
