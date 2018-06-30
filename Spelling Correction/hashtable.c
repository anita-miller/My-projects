/* ... */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spell.h"
#include "hashtable.h"
#include <assert.h>



Bucket *new_bucket() {
	Bucket *bucket = malloc(sizeof *bucket);
	assert(bucket);

	// create own copy of key for storage in table
/*	bucket->key = malloc((sizeof *bucket->key) * (strlen(key) + 1));
	assert(bucket->key);
	strcpy(bucket->key, key);

	bucket->value = value;*/
	//bucket->next = NULL;

	return bucket;

}

// Warning: does not free bucket->next
void free_bucket(Bucket *bucket) {
	assert(bucket != NULL);
//	free(bucket->key);
	free(bucket);
}

// create a new, empty list and return its pointer
List_t *new_list_t() {
	List_t *list = malloc(sizeof *list);
	assert(list);

	list->head = NULL;
	list->last = NULL;
	list->size = 0;

	return list;

}

// destroy a list and free its memory
// DOES NOT FREE POINTERS TO DATA HELD IN THE LISTS NODES, only frees the nodes
void free_list_t(List_t *list) {
	assert(list != NULL);
	// free each node
	Bucket *bucket = list->head;
	Bucket *next;
	while (bucket != NULL) {
		next = bucket->next;
		free_bucket(bucket);
		bucket = next;
	}

}

// add an element to the front of a list
// this operation is O(1)
void list_t_add_start(List_t *list,char *key, int value){
	assert(list != NULL);
	if(key == NULL && value == 0){
		return;
	}

	// create and initialise a new list node
	Bucket *bucket = new_bucket();
	bucket->key = key;
	bucket->value = value;
  bucket->next = list->head;
	// place it at the start of the list
	list->head = bucket;

	// if list was empty, this new node is also the last node now
	if(list->size == 0) {
		list->last = bucket;
	}
	// and we need to keep size updated!
	list->size++;

}

// xor hash from lectures, with seed 73802
unsigned int seed = 73802;
unsigned int xor_hash(char string[], int m){
int i; char c; unsigned int h;
    h = seed;
    for( i = 0 ; ( c=string[i] ) !='\0' ; i++ )
              h = h ^ ( (h << 5) + c + (h >> 2) );
    return((unsigned int)( h % m ));
}


/* * *
 * HASH TABLE CREATION/DELETION
 */

HashTable *new_hash_table(int size) {
	HashTable *table = malloc(sizeof *table);
	assert(table);

	table->nslots = size;
	table->lists = malloc(size * (sizeof *table->lists));
	assert(table->lists);
	int i;
	for (i = 0; i < size; i++) {
		table->lists[i] = *new_list_t();
	}

	return table;
}

void free_hash_table(HashTable *table) {
	assert(table != NULL);

	int i;
	for (i = 0; i < table->nslots; i++) {
		free_list_t(&table->lists[i]);
	}
	free(table->lists);
	free(table);
}

/* * *
 * HASHING HELPER FUNCTIONS
 */

bool equal(char *a, char *b) {
	return strcmp(a, b) == 0;
}

/* * *
 * HASH TABLE FUNCTIONS
 */

void hash_table_put(HashTable *table, char *key, int value) {
	assert(table != NULL);
	assert(key != NULL);

	int hash_value = xor_hash(key, table->nslots);

	list_t_add_start(&table->lists[hash_value], key, value);
  table->nitems++;
}

char* hash_table_get(HashTable *table, char *key) {
	assert(table != NULL);
	assert(key != NULL);

	int hash_value = xor_hash(key, table->nslots);

	// look for existing key

	while (table->lists[hash_value].head) {
    Bucket *bucket = table->lists[hash_value].head;
    if (equal(key, bucket->key)) {
			return key;
		}
		table->lists[hash_value].head = table->lists[hash_value].head->next;
	}
  return NULL;
}

bool hash_table_has(HashTable *table, char *key) {
	assert(table != NULL);
	assert(key != NULL);

	int hash_value = xor_hash(key, table->nslots);

	// look for existing key
  while (table->lists[hash_value].head) {
    if (equal(key, table->lists[hash_value].head->key)) {

			return true;
		}
		table->lists[hash_value].head = table->lists[hash_value].head->next;
	}
	// key doesn't exist!
	return false;
}


//read the dictionary into hashtable
void dictionary_to_hashtable(List *dictionary, HashTable hashtable){
    int position = 0;
		//read through nodes in dictionary
		while(dictionary->head){
      position++;

			hash_table_put(&hashtable,((char *)dictionary->head->data), position);
      //go to the next node
			dictionary->head= dictionary->head->next;
		}
}
