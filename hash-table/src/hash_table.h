#ifndef _HASH_TABLE
#define _HASH_TABLE

struct hash_table_kv_pair {
  char *key;
  char *value;
};

struct hash_table {
  int size;
  int count;
  hash_table_kv_pair **pair;
};

struct hash_table hash_table_new();
void del_hash_table(hash_table *ht);

#endif /* _HASH_TABLE */
