#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static struct hash_table_kv_pair *hash_table_kv_pair_new(const char *k,
                                                         const char *v) {
  struct hash_table_kv_pair *pair = malloc(sizeof(struct hash_table_kv_pair));
  pair->key = strdup(k);
  pair->value = strdup(v);
  return pair;
}

struct hash_table *hash_table_new(void) {
  struct hash_table *ht = malloc(sizeof(struct hash_table));

  ht->size = 53;
  ht->count = 0;
  ht->pairs = calloc((size_t)ht->size, sizeof(struct hash_table_kv_pair *));
  return ht;
}

static void del_hash_table_kv_pair(struct hash_table_kv_pair *pair) {
  free(pair->key);
  free(pair->value);
  free(pair);
}

void del_hash_table(struct hash_table *ht) {
  for (int i = 0; i < ht->size; i++) {
    struct hash_table_kv_pair *pair = ht->pairs[i];
    if (pair == NULL)
      continue;
    del_hash_table_kv_pair(pair);
  }

  free(ht->pairs);
  free(ht);
}
