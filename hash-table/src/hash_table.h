#ifndef _HASH_TABLE
#define _HASH_TABLE

struct hash_table_kv_pair {
  char *key;
  char *value;
};

struct hash_table {
  int size;
  int count;
  struct hash_table_kv_pair **pairs;
};

struct hash_table *hash_table_new(void);
void del_hash_table(struct hash_table *ht);

#endif /* _HASH_TABLE */
