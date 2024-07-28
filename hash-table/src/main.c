#include  "hash_table.h"

int main(int argc, char *argv[]) {
  struct hash_table *ht = hash_table_new();
  del_hash_table(ht);
}
