#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct htpair {
  char *key;
  char *value;
};

struct ht {
  int base_size;
  int size;
  int count;
  struct htpair **pairs;
};

struct ht *ht_new(void);
void ht_delete(struct ht *ht);

char *htpair_get_value(struct ht *ht, const char *key);
void htpair_insert(struct ht *ht, const char *key, const char *value);
void htpair_delete(struct ht *ht, const char *key);

#endif /* HASH_TABLE_H */
