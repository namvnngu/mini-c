#include "hash_table.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct hash_table *ht = hash_table_new();

  printf("hash table size: %d\n", ht->size);

  printf("before:\n");

  hash_table_pair_insert(ht, "name", "John");
  hash_table_pair_insert(ht, "age", "18");
  hash_table_pair_insert(ht, "phone", "0123456789");
  printf("name: %s\n", hash_table_pair_get_value(ht, "name"));
  printf("age: %s\n", hash_table_pair_get_value(ht, "age"));
  printf("phone: %s\n", hash_table_pair_get_value(ht, "phone"));
  printf("hash table size: %d\n", ht->size);

  printf("after:\n");

  hash_table_pair_insert(ht, "name", "Leo");
  hash_table_pair_insert(ht, "age", "19");
  hash_table_pair_delete(ht, "phone");
  printf("name: %s\n", hash_table_pair_get_value(ht, "name"));
  printf("age: %s\n", hash_table_pair_get_value(ht, "age"));
  printf("phone: %s\n", hash_table_pair_get_value(ht, "phone"));
  printf("hash table size: %d\n", ht->size);

  hash_table_delete(ht);
}
