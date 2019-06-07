#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// C requires importing system / header files
// This is when you import functionalities from other libraries. 
//These could contain functions that you would like to use in  your program so you have to import them. 
//You typically include these at the top of your C file. 
//These could be header files from the standard library or header files that you write.

// Hash tables notes:

// What are has tables?
// Data structure behind:
// 	- Associative Arrays and Dictionaries
// 	- Objects (Python, Javascript, Ruby)
// 	- Caches (Memcached)
// 	- Dynamic Programming, Memoization 

// How does a hash table work?
// 	- Key/Value data storage and retrieval
// 	- Data is stored in contiguous block of memory as an array
// 	- The key is converted to an integer via a has function
// 	- The hashed key is converted to an array index via modulo function

// Hash table is:
// hash_table[Key] = Value;

// // Pseudocode
// // int index = hash_function(Key) % array.length;
// // array[index] = Value;

// What is a Hash Function?
// - One-way mapping from arbitrary data to fixed data size and type

// - Many different has functions with different attributes:
// 	- Deterministic
// 	- Uniform Distribution
// 	- Non-invertible
// 	- Continuous vs. non-continuous 

// Hash function:

// // Sums the ascii values of the characters in a string and returns a modulo
// // String -> integer(0, 31)

// int basic_string_hash(char str[]) {
// {
// 	int hash = 0;
// 	for (int i = 0; str[i] != '\0'; i++) {
// 	hash += str[i];
// }
// return has % 32;
// }

// basic_string_hash("Hello");
// // ['H', 'e', 'l', 'l', 'o'] -> {72, 101, 108, 111] -> 500
// // 500 % 32 = 20

// basic_string_hash("World");
// // 'W', 'o', 'r', 'l', 'd'] -> [87, 111, 114, 108, 100] -> 520
// // 520 % 32 = 8

// How do hash tables work?

// 1. Declare an empty array
// 	- Power of 2 (32)
// 	- arr = malloc (DEFAULT_SIZE * sizeof (VALUE_TYPE));
// 2. Hash the key
// 	- basic_string_hash("Hello') - >20
// 3. Assign Value to hash index
// 	- arr[20] = Value;

// What are hash table collisions?
// 	- Two keys has to the same index
// 	- How can we avoid collisions?
// 	- What are the chances of a collision?

// Look up the Birthday Problem on wiki.
// - Collision Probability = 1 - k! / ((k-n)! * k ^n)
// - Takeaway: Collisions are unavoidable

// Handling Collisions:
// There are many different methods:
// 	- Open addressing
// 	- Linked list chaining 

// Linked List Chaining:
// 	- Elements in the has table are stored as linked lists
// 	- When retrieving a value, traverse down the linked list until you find the 	matching key

// Linke list chaining performance:
// - Time complexity
// - Insert, delete, and search for linked lists are O(n) 
// - Space complexity
// 	- Must store key, value and pointer for each hash table
// 	- Empty slots	
// 	- Still O(n)

// Hash Table Resizing 
// - Load factor = (number of entires) / (hash table capacity)
// - When load factor passes a certain threshold, resizing can occur
// 	- Create a new has table with double capacity
// 	- Copy elements from the old hash table to the new one. One at a time.
// 	- Resizing is O(n) BUT occurs at O(log n) frequency 


// ## DAY 1
// Your assignment is to implement a basic hash table in the `basic_hash_table` directory. 
// You should be able to insert, read, and delete elements from the hash table. 
// You do not need to handle collisions but should print a warning when you are overwriting an existing value.
// Build your code by typing `make` then `./b_hashtable` in the terminal.
// Run tests by typing `make tests`.

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
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


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  if (capacity < 1) {
    return NULL;
  }

  BasicHashTable *ht = malloc(sizeof(BasicHashTable));
  if (ht == NULL) {
    return NULL;
  }

  ht->storage = calloc(capacity, sizeof(Pair)); // The difference in malloc and calloc is that malloc does not set the memory to zero where as calloc sets allocated memory to zero.
  if (ht->storage == NULL) {
    return (NULL);
  }

  ht->capacity = capacity;

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  int i = hash(key, ht->capacity);
  if (ht->storage[i] != NULL)
  {
    printf("\n** WARNING: overwriting previous values! **\n");
    printf("\n");
    destroy_pair(ht->storage[i]);
    ht->storage[i] = create_pair(key, value);
  }
  else
  {
    ht->storage[i] = create_pair(key, value);
  }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  unsigned int i;
  if (ht == NULL) {
    return;
  }

  i = hash(key, ht->capacity);
    if (ht->storage[i] != NULL)
    {
      printf("\n** Removing an entry! **\n");
      printf("\n");
      destroy_pair(ht->storage[i]);
      ht->storage[i] = NULL;
  }

}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  int i = hash(key, ht->capacity);
  if (ht->storage[i] != NULL)
  {
    return ht->storage[i]->value;
  }
  printf("\n** Error! Was not able to retrieve the entry. **\n");
  printf("\n");
  return NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  int i;
  if(ht == NULL) {
    return;
  }

  for (i = 0; i < ht->capacity; i++) {
  if (ht->storage[i] != NULL) {
    destroy_pair(ht->storage[i]);
    }
  }
    free(ht->storage);
    free(ht);

}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
