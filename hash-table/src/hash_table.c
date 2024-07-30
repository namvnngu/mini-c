#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "prime.h"

static const int HASH_TABLE_PRIME_1 = 151;
static const int HASH_TABLE_PRIME_2 = 163;
static const int HASH_TABLE_INITIAL_BASE_SIZE = 50;
static struct hash_table_pair HASH_TABLE_DELETED_PAIR = {NULL, NULL};
static const int HASH_TABLE_LOAD_RANGE[2] = {10, 70};

static struct hash_table_pair *create_hash_table_pair(const char *k,
                                                      const char *v) {
  struct hash_table_pair *pair = malloc(sizeof(struct hash_table_pair));
  pair->key = strdup(k);
  pair->value = strdup(v);
  return pair;
}

static void exit_out_of_memory(void) {
  fprintf(stderr, "Out of memory.");
  exit(1);
}

static struct hash_table *create_sized_hash_table(const int base_size) {
  struct hash_table *ht = malloc(sizeof(struct hash_table));
  if (ht == NULL)
    exit_out_of_memory();

  ht->base_size = base_size;
  ht->size = next_prime(ht->base_size);
  ht->count = 0;

  ht->pairs = calloc((size_t)ht->size, sizeof(struct hash_table_pair *));
  if (ht->pairs == NULL)
    exit_out_of_memory();

  return ht;
}

static void reisze_hash_table(struct hash_table *ht, const int base_size) {
  if (base_size < HASH_TABLE_INITIAL_BASE_SIZE)
    return;

  struct hash_table *new_ht = create_sized_hash_table(base_size);
  for (int i = 0; i < ht->size; i++) {
    struct hash_table_pair *pair = ht->pairs[i];
    if (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR)
      insert_hash_table_pair(new_ht, pair->key, pair->value);
  }

  ht->base_size = new_ht->base_size;
  ht->count = new_ht->count;
  ht->size = new_ht->size;

  struct hash_table_pair **temp_pairs = ht->pairs;
  ht->pairs = new_ht->pairs;
  new_ht->pairs = temp_pairs;

  delete_hash_table(new_ht);
}

static void resize_up_hash_table(struct hash_table *ht) {
  const int new_size = ht->base_size * 2;
  reisze_hash_table(ht, new_size);
}

static void resize_down_hash_table(struct hash_table *ht) {
  const int new_size = ht->base_size / 2;
  reisze_hash_table(ht, new_size);
}

static void _delete_hash_table_pair(struct hash_table_pair *pair) {
  free(pair->key);
  free(pair->value);
  free(pair);
}

static int hash(const char *s, const int a, const int m) {
  long h = 0;
  const int len_s = strlen(s);

  for (int i = 0; i < len_s; i++)
    h += (long)pow(a, len_s - (i + 1)) * s[i];

  h = h % m;
  return (int)h;
}

static int get_hash(const char *s, const int num_buckets, const int attempt) {
  const int hash_a = hash(s, HASH_TABLE_PRIME_1, num_buckets);
  if (attempt == 0)
    return hash_a;
  int hash_b = hash(s, HASH_TABLE_PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

static int cal_hash_table_load(struct hash_table *ht) {
  return ht->count * 100 / ht->size;
}

struct hash_table *create_hash_table(void) {
  return create_sized_hash_table(HASH_TABLE_INITIAL_BASE_SIZE);
}

void delete_hash_table(struct hash_table *ht) {
  for (int i = 0; i < ht->size; i++) {
    struct hash_table_pair *pair = ht->pairs[i];
    if (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR)
      _delete_hash_table_pair(pair);
  }

  free(ht->pairs);
  free(ht);
}

char *get_hash_table_pair_value(struct hash_table *ht, const char *key) {
  int index = get_hash(key, ht->size, 0);
  struct hash_table_pair *pair = ht->pairs[index];

  int i = 1;
  while (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR) {
    if (strcmp(pair->key, key) == 0)
      return pair->value;

    index = get_hash(key, ht->size, i);
    pair = ht->pairs[index];
    i++;
  }

  return NULL;
}

void insert_hash_table_pair(struct hash_table *ht, const char *key,
                            const char *value) {
  if (cal_hash_table_load(ht) > HASH_TABLE_LOAD_RANGE[1])
    resize_up_hash_table(ht);

  struct hash_table_pair *pair = create_hash_table_pair(key, value);

  int index = get_hash(pair->key, ht->size, 0);
  struct hash_table_pair *curr_pair = ht->pairs[index];

  int i = 1;
  while (curr_pair != NULL && curr_pair != &HASH_TABLE_DELETED_PAIR) {
    if (strcmp(curr_pair->key, key) == 0) {
      _delete_hash_table_pair(curr_pair);
      ht->pairs[index] = pair;
      return;
    }
    index = get_hash(pair->key, ht->size, i);
    curr_pair = ht->pairs[index];
    i++;
  }

  ht->pairs[index] = pair;
  ht->count++;
}

void delete_hash_table_pair(struct hash_table *ht, const char *key) {
  if (cal_hash_table_load(ht) < HASH_TABLE_LOAD_RANGE[0])
    resize_down_hash_table(ht);

  int index = get_hash(key, ht->size, 0);
  struct hash_table_pair *pair = ht->pairs[index];

  int i = 1;
  while (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR) {
    if (strcmp(pair->key, key) == 0) {
      _delete_hash_table_pair(pair);
      ht->pairs[index] = &HASH_TABLE_DELETED_PAIR;
      ht->count--;
      return;
    }

    index = get_hash(key, ht->size, i);
    pair = ht->pairs[index];
    i++;
  }
}
