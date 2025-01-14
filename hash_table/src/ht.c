#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ht.h"
#include "prime.h"

static const int HT__PRIME_1 = 151;
static const int HT__PRIME_2 = 163;
static const int HT__INITIAL_BASE_SIZE = 50;
static struct htpair HT__DELETED_PAIR = { NULL, NULL };
static const int HT__LOAD_RANGE[2] = { 10, 70 };

static struct htpair *htpair__new(const char *k, const char *v) {
  struct htpair *pair = malloc(sizeof(struct htpair));
  pair->key = strdup(k);
  pair->value = strdup(v);
  return pair;
}

static void ht__exit_out_of_memory(void) {
  fprintf(stderr, "Out of memory.");
  exit(1);
}

static struct ht *ht__new_with_size(const int base_size) {
  struct ht *ht = malloc(sizeof(struct ht));
  if (ht == NULL) {
    ht__exit_out_of_memory();
  }

  ht->base_size = base_size;
  ht->size = next_prime(ht->base_size);
  ht->count = 0;

  ht->pairs = calloc((size_t)ht->size, sizeof(struct htpair *));
  if (ht->pairs == NULL) {
    ht__exit_out_of_memory();
  }

  return ht;
}

static void ht__resize(struct ht *ht, const int base_size) {
  if (base_size < HT__INITIAL_BASE_SIZE) {
    return;
  }

  struct ht *new_ht = ht__new_with_size(base_size);
  for (int i = 0; i < ht->size; i++) {
    struct htpair *pair = ht->pairs[i];
    if (pair != NULL && pair != &HT__DELETED_PAIR) {
      htpair_insert(new_ht, pair->key, pair->value);
    }
  }

  ht->base_size = new_ht->base_size;
  ht->count = new_ht->count;
  ht->size = new_ht->size;

  struct htpair **temp_pairs = ht->pairs;
  ht->pairs = new_ht->pairs;
  new_ht->pairs = temp_pairs;

  ht_delete(new_ht);
}

static void ht__resize_up(struct ht *ht) {
  const int new_size = ht->base_size * 2;
  ht__resize(ht, new_size);
}

static void ht__resize_down(struct ht *ht) {
  const int new_size = ht->base_size / 2;
  ht__resize(ht, new_size);
}

static void htpair__delete(struct htpair *pair) {
  free(pair->key);
  free(pair->value);
  free(pair);
}

static int ht__hash(const char *s, const int a, const int m) {
  long h = 0;
  const int len_s = strlen(s);

  for (int i = 0; i < len_s; i++) {
    h += (long)pow(a, len_s - (i + 1)) * s[i];
  }

  h = h % m;
  return (int)h;
}

static int ht__gethash(const char *s,
                       const int num_buckets,
                       const int attempt) {
  const int hash_a = ht__hash(s, HT__PRIME_1, num_buckets);
  if (attempt == 0) {
    return hash_a;
  }
  int hash_b = ht__hash(s, HT__PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

static int ht__calc_load(struct ht *ht) {
  return ht->count * 100 / ht->size;
}

struct ht *ht_new(void) {
  return ht__new_with_size(HT__INITIAL_BASE_SIZE);
}

void ht_delete(struct ht *ht) {
  for (int i = 0; i < ht->size; i++) {
    struct htpair *pair = ht->pairs[i];
    if (pair != NULL && pair != &HT__DELETED_PAIR) {
      htpair__delete(pair);
    }
  }

  free(ht->pairs);
  free(ht);
}

char *htpair_get_value(struct ht *ht, const char *key) {
  int index = ht__gethash(key, ht->size, 0);
  struct htpair *pair = ht->pairs[index];

  int i = 1;
  while (pair != NULL && pair != &HT__DELETED_PAIR) {
    if (strcmp(pair->key, key) == 0) {
      return pair->value;
    }

    index = ht__gethash(key, ht->size, i);
    pair = ht->pairs[index];
    i++;
  }

  return NULL;
}

void htpair_insert(struct ht *ht, const char *key, const char *value) {
  if (ht__calc_load(ht) > HT__LOAD_RANGE[1]) {
    ht__resize_up(ht);
  }

  struct htpair *pair = htpair__new(key, value);

  int index = ht__gethash(pair->key, ht->size, 0);
  struct htpair *curr_pair = ht->pairs[index];

  int i = 1;
  while (curr_pair != NULL && curr_pair != &HT__DELETED_PAIR) {
    if (strcmp(curr_pair->key, key) == 0) {
      htpair__delete(curr_pair);
      ht->pairs[index] = pair;
      return;
    }
    index = ht__gethash(pair->key, ht->size, i);
    curr_pair = ht->pairs[index];
    i++;
  }

  ht->pairs[index] = pair;
  ht->count++;
}

void htpair_delete(struct ht *ht, const char *key) {
  if (ht__calc_load(ht) < HT__LOAD_RANGE[0]) {
    ht__resize_down(ht);
  }

  int index = ht__gethash(key, ht->size, 0);
  struct htpair *pair = ht->pairs[index];

  int i = 1;
  while (pair != NULL && pair != &HT__DELETED_PAIR) {
    if (strcmp(pair->key, key) == 0) {
      htpair__delete(pair);
      ht->pairs[index] = &HT__DELETED_PAIR;
      ht->count--;
      return;
    }

    index = ht__gethash(key, ht->size, i);
    pair = ht->pairs[index];
    i++;
  }
}
