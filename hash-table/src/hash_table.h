#ifndef _HASH_TABLE
#define _HASH_TABLE

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

struct hash_table *create_hash_table(void);
void delete_hash_table(struct hash_table *ht);

char *get_hash_table_pair_value(struct hash_table *ht, const char *key);
void insert_hash_table_pair(struct hash_table *ht, const char *key,
                            const char *value);
void delete_hash_table_pair(struct hash_table *ht, const char *key);

#endif /* _HASH_TABLE */
