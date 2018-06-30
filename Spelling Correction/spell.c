/* ... */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spell.h"
#include "list.h"
#include "hashtable.h"
#include "edit_calc.h"
#include <time.h>
#include <assert.h>
#include <math.h>


// see Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2) {
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	int distance;
	distance = edit_distance(word1, word2, len1, len2);
	printf ("%d \n", distance);
}


// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {

	char *temp = malloc(MAXIMUM_WORD_LEN);

	//deletion of single letter: making words 1 edit from "word"
	for(int i = 0; i < strlen(word); i++){
		strcpy(temp, word);
		memmove(&temp[i], &temp[i+1], strlen(word)- i);
		printf("%s\n", temp);
	}
	//substituting a single letter in word
	for(int m = 0; m < strlen(word); m++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, word);
			temp[m] = l;
			printf("%s\n",temp);
		}
	}

	//inserting a single letter into word
	for(int m = 0; m < strlen(word)+2; m++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, word);
			append(temp, &l , m);
			printf("%s\n",temp);
		}
	}
	free(temp);
}


// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	//create a hashtable
	HashTable *hashtable = new_hash_table(dictionary->size);

	//read the dictionary into hashtable
	dictionary_to_hashtable(dictionary, *hashtable);

	//iterate through nodes in documents
	while(document->head){
		//search for the word in hashtable
		//if it exists print the word
		if(hash_table_has(hashtable, ((char *)document->head->data))){

			printf("%s\n",((char *)document->head->data));
		}
		//it the word isnt in the hashtable print with ?
		else{
			printf("%s?\n",((char *)document->head->data));
		}

		document->head= document->head->next;

	}
	free_hash_table(hashtable);


}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {

	HashTable *hashtable = new_hash_table(dictionary->size);
	HashTable *hashtable_edits = new_hash_table(dictionary->size);
	//read the dictionary into hashtable
	Node* dict_head = dictionary->head;
	dictionary_to_hashtable(dictionary,*hashtable);
	dictionary->head = dict_head;

	//iterate through nodes in documents
	while(document->head){
		int min_value = 0;
		char * min_str = NULL;

		//create hash key for each word
		int hash_value = xor_hash(((char *)document->head->data), hashtable->nslots);

			//search for the word in hashtable
			//if it exists print the word
			if(hash_table_has(hashtable, ((char *)document->head->data))){
				printf("%s\n", hashtable->lists[hash_value].head->key);
			}
			else{

				char *temp = malloc(MAXIMUM_WORD_LEN);

				//find one edit distance away edits and if they were in dictionary print them
				one_editdistance(((char *)document->head->data), dictionary, *hashtable, *hashtable_edits, hash_value, temp, min_value, min_str);

				//if the word didnt have any one edit distance away that exist in dictionary
				if(hashtable_edits->lists[hash_value].size == 0){
					//find two edit distance away edits and if they were in dictionary print them
					two_editdistance(((char *)document->head->data), dictionary, dict_head, *hashtable, *hashtable_edits, hash_value, temp, min_value, min_str);
				}

				//if the word didnt have any one or two edit distance away that exist in dictionary
				if(hashtable_edits->lists[hash_value].size == 0){
					//find three edit distance away edits and if they were in dictionary print them
					three_editdistance(((char *)document->head->data), dictionary, dict_head, *hashtable, *hashtable_edits, hash_value, temp, min_value, min_str);
				}

				//if the word didnt have any one, two or three edit distance away that exist in dictionary
				if(hashtable_edits->lists[hash_value].size == 0){
					printf("%s?\n", ((char *)document->head->data));
				}

			//refresh the hashtable for edits so it can work for repeated words
			for (int m = 0; m < hashtable_edits->nslots; m++) {
				hashtable_edits->lists[m].head = NULL;
				hashtable_edits->lists[m].last = NULL;
				hashtable_edits->lists[m].size = 0;

			}
			free(temp);
		}

		document->head= document->head->next;
	}
	free_hash_table(hashtable);
	free_hash_table(hashtable_edits);

}
