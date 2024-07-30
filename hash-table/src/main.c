#include "hash_table.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct hash_table *ht = create_hash_table();

  printf("hash table size: %d\n", ht->size);

  printf("before:\n");

  insert_hash_table_pair(ht, "name", "John");
  insert_hash_table_pair(ht, "age", "18");
  insert_hash_table_pair(ht, "phone", "0123456789");
  printf("name: %s\n", get_hash_table_pair_value(ht, "name"));
  printf("age: %s\n", get_hash_table_pair_value(ht, "age"));
  printf("phone: %s\n", get_hash_table_pair_value(ht, "phone"));
  printf("hash table size: %d\n", ht->size);

  printf("after:\n");

  insert_hash_table_pair(ht, "name", "Leo");
  insert_hash_table_pair(ht, "age", "19");
  delete_hash_table_pair(ht, "phone");
  printf("name: %s\n", get_hash_table_pair_value(ht, "name"));
  printf("age: %s\n", get_hash_table_pair_value(ht, "age"));
  printf("phone: %s\n", get_hash_table_pair_value(ht, "phone"));
  printf("hash table size: %d\n", ht->size);

  delete_hash_table(ht);
}
