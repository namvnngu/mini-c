#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct hash_table_pair {
  char *key;
  char *value;
};

struct hash_table {
  int base_size;
  int size;
  int count;
  struct hash_table_pair **pairs;
};

struct hash_table *hash_table_new(void);
void hash_table_delete(struct hash_table *ht);

char *hash_table_pair_get_value(struct hash_table *ht, const char *key);
void hash_table_pair_insert(struct hash_table *ht, const char *key,
                            const char *value);
void hash_table_pair_delete(struct hash_table *ht, const char *key);

#endif /* HASH_TABLE_H */
