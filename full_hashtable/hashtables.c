#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// C requires importing system / header files
// This is when you import functionalities from other libraries. 
//These could contain functions that you would like to use in  your program so you have to import them. 
//You typically include these at the top of your C file. 
//These could be header files from the standard library or header files that you write.

// ## DAY 2
// Your assignment is to upgrade your basic hash table to handle collisions with 
// linked list chaining. You should be able to insert an arbitrary amount of 
// elements into your hash table, regardless of table size, 
// and read them back without any data loss. 
// You should also implement a resizing function that doubles the size of 
// your hash table and copies all elements into the new data structure.
// Build your code by typing `make` then `./hashtable` in the terminal.
// Run tests by typing `make tests`.

/*
  Hash table key/value pair with linked list pointer.

  Note that an instance of `LinkedPair` is also a node in a linked list.
  More specifically, the `next` field is a pointer pointing to the the 
  next `LinkedPair` in the list of `LinkedPair` nodes. 
 */
typedef struct LinkedPair {
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/*
  Hash table with linked pairs.
 */
typedef struct HashTable {
  int capacity;
  LinkedPair **storage;
} HashTable;

/*
  Create a key/value linked pair to be stored in the hash table.
 */
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = strdup(key);
  pair->value = strdup(value);
  pair->next = NULL;

  return pair;
}

/*
  Use this function to safely destroy a hashtable pair.
 */
void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/*
  djb2 hash function

  Do not modify this!
 */
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/*
  Fill this in.

  All values in storage should be initialized to NULL
 */
HashTable *create_hash_table(int capacity)
{
  if (capacity < 1) {
    return NULL;
  }

  HashTable *ht = malloc(sizeof(HashTable));
  if (ht == NULL) {
    return NULL;
  }

  ht->storage = calloc(capacity, sizeof(LinkedPair *)); // The difference in malloc and calloc is that malloc does not set the memory to zero where as calloc sets allocated memory to zero.
  if(ht->storage == NULL) {
    return (NULL);
  }
  
  ht->capacity = capacity;

  return ht;
}

/*
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 */
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  unsigned int i = hash(key, ht->capacity); // unsigned int if bucket list is over 2 billion
  // The difference between unsigned int and a signed int is that the last bit is used to do positive or negative.
  LinkedPair *current = ht->storage[i];
  LinkedPair *last;

  while (current != NULL && strcmp(current->key, key) != 0)
  {
    last = current;
    current = last->next;
  }

  if (current != NULL)
  {
    printf("** This is an existing key and the value will be overwritten in th existing LinkedPair list. **\n");
    current->value = value;
  }
  else
  {
    LinkedPair *new = create_pair(key, value);
    new->next = ht->storage[i];
    ht->storage[i] = new;
  }
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 */
void hash_table_remove(HashTable *ht, char *key)
{

}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 */
char *hash_table_retrieve(HashTable *ht, char *key)
{
  return NULL;
}

/*
  Fill this in.

  Don't forget to free any malloc'ed memory!
 */
void destroy_hash_table(HashTable *ht)
{

}

/*
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 */
HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht;

  return new_ht;
}


#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");

  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));

  int old_capacity = ht->capacity;
  ht = hash_table_resize(ht);
  int new_capacity = ht->capacity;

  printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
