/* * * * * * *
 * Module for functions that solve the coding tasks from assignment 2
 *
 * created for COMP20007 Design of Algorithms - Assignment 2, 2018
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAXIMUM_WORD_LEN 256

typedef struct bucket Bucket;
struct bucket {
	char *key;
	int value;
	Bucket *next;
};

typedef struct list_t List_t;
struct list_t {
	Bucket *head; // pointer to the first node in the list
	Bucket *last; // pointer to the last node in the list
	int size;	// number of nodes currently in the list
};


typedef struct HashTabRep HashTable;
struct HashTabRep {
	int nitems;
	int nslots;
	List_t *lists;
};

Bucket *new_bucket();
void free_bucket(Bucket *bucket);
List_t *new_list_t();
void free_list_t(List_t *list);
void list_t_add_start(List_t *list,char *key, int value);
unsigned int xor_hash(char string[], int m);
HashTable *new_hash_table(int size);
void free_hash_table(HashTable *table);
int h(char *key, int size);
bool equal(char *a, char *b);
void hash_table_put(HashTable *table, char *key, int value);
char* hash_table_get(HashTable *table, char *key);
bool hash_table_has(HashTable *table, char *key);
void dictionary_to_hashtable(List *dictionary, HashTable hashtable);

#endif
