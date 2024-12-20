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

static struct hash_table_pair *_hash_table_pair_new(const char *k,
                                                    const char *v) {
  struct hash_table_pair *pair = malloc(sizeof(struct hash_table_pair));
  pair->key = strdup(k);
  pair->value = strdup(v);
  return pair;
}

static void _exit_out_of_memory(void) {
  fprintf(stderr, "Out of memory.");
  exit(1);
}

static struct hash_table *_sized_hash_table_new(const int base_size) {
  struct hash_table *ht = malloc(sizeof(struct hash_table));
  if (ht == NULL)
    _exit_out_of_memory();

  ht->base_size = base_size;
  ht->size = next_prime(ht->base_size);
  ht->count = 0;

  ht->pairs = calloc((size_t)ht->size, sizeof(struct hash_table_pair *));
  if (ht->pairs == NULL)
    _exit_out_of_memory();

  return ht;
}

static void _hash_table_resize(struct hash_table *ht, const int base_size) {
  if (base_size < HASH_TABLE_INITIAL_BASE_SIZE)
    return;

  struct hash_table *new_ht = _sized_hash_table_new(base_size);
  for (int i = 0; i < ht->size; i++) {
    struct hash_table_pair *pair = ht->pairs[i];
    if (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR)
      hash_table_pair_insert(new_ht, pair->key, pair->value);
  }

  ht->base_size = new_ht->base_size;
  ht->count = new_ht->count;
  ht->size = new_ht->size;

  struct hash_table_pair **temp_pairs = ht->pairs;
  ht->pairs = new_ht->pairs;
  new_ht->pairs = temp_pairs;

  hash_table_delete(new_ht);
}

static void _hash_table_resize_up(struct hash_table *ht) {
  const int new_size = ht->base_size * 2;
  _hash_table_resize(ht, new_size);
}

static void _hash_table_resize_down(struct hash_table *ht) {
  const int new_size = ht->base_size / 2;
  _hash_table_resize(ht, new_size);
}

static void _hash_table_pair_delete(struct hash_table_pair *pair) {
  free(pair->key);
  free(pair->value);
  free(pair);
}

static int _hash(const char *s, const int a, const int m) {
  long h = 0;
  const int len_s = strlen(s);

  for (int i = 0; i < len_s; i++)
    h += (long)pow(a, len_s - (i + 1)) * s[i];

  h = h % m;
  return (int)h;
}

static int _hash_table_get_hash(const char *s, const int num_buckets,
                                const int attempt) {
  const int hash_a = _hash(s, HASH_TABLE_PRIME_1, num_buckets);
  if (attempt == 0)
    return hash_a;
  int hash_b = _hash(s, HASH_TABLE_PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

static int _hash_table_calc_load(struct hash_table *ht) {
  return ht->count * 100 / ht->size;
}

struct hash_table *hash_table_new(void) {
  return _sized_hash_table_new(HASH_TABLE_INITIAL_BASE_SIZE);
}

void hash_table_delete(struct hash_table *ht) {
  for (int i = 0; i < ht->size; i++) {
    struct hash_table_pair *pair = ht->pairs[i];
    if (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR)
      _hash_table_pair_delete(pair);
  }

  free(ht->pairs);
  free(ht);
}

char *hash_table_pair_get_value(struct hash_table *ht, const char *key) {
  int index = _hash_table_get_hash(key, ht->size, 0);
  struct hash_table_pair *pair = ht->pairs[index];

  int i = 1;
  while (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR) {
    if (strcmp(pair->key, key) == 0)
      return pair->value;

    index = _hash_table_get_hash(key, ht->size, i);
    pair = ht->pairs[index];
    i++;
  }

  return NULL;
}

void hash_table_pair_insert(struct hash_table *ht, const char *key,
                            const char *value) {
  if (_hash_table_calc_load(ht) > HASH_TABLE_LOAD_RANGE[1])
    _hash_table_resize_up(ht);

  struct hash_table_pair *pair = _hash_table_pair_new(key, value);

  int index = _hash_table_get_hash(pair->key, ht->size, 0);
  struct hash_table_pair *curr_pair = ht->pairs[index];

  int i = 1;
  while (curr_pair != NULL && curr_pair != &HASH_TABLE_DELETED_PAIR) {
    if (strcmp(curr_pair->key, key) == 0) {
      _hash_table_pair_delete(curr_pair);
      ht->pairs[index] = pair;
      return;
    }
    index = _hash_table_get_hash(pair->key, ht->size, i);
    curr_pair = ht->pairs[index];
    i++;
  }

  ht->pairs[index] = pair;
  ht->count++;
}

void hash_table_pair_delete(struct hash_table *ht, const char *key) {
  if (_hash_table_calc_load(ht) < HASH_TABLE_LOAD_RANGE[0])
    _hash_table_resize_down(ht);

  int index = _hash_table_get_hash(key, ht->size, 0);
  struct hash_table_pair *pair = ht->pairs[index];

  int i = 1;
  while (pair != NULL && pair != &HASH_TABLE_DELETED_PAIR) {
    if (strcmp(pair->key, key) == 0) {
      _hash_table_pair_delete(pair);
      ht->pairs[index] = &HASH_TABLE_DELETED_PAIR;
      ht->count--;
      return;
    }

    index = _hash_table_get_hash(key, ht->size, i);
    pair = ht->pairs[index];
    i++;
  }
}
