/* ... */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spell.h"
#include "hashtable.h"
#include <math.h>
#include <assert.h>

#define TWO_EDITDISTANCE 2
#define THREE_EDITDISTANCE 3

// retrun the edit distance between 2 chars
int edit_distance(char *word1, char *word2, int len1, int len2) {
	int matrix[strlen(word1) + 1][strlen(word2) + 1];
	int i;
	for (i = 0; i <= len1; i++) {
			matrix[i][0] = i;
	}
	for (i = 0; i <= len2; i++) {
			matrix[0][i] = i;
	}
	for (i = 1; i <= len1; i++) {
			int j;
			char c1;

			c1 = word1[i-1];
			for (j = 1; j <= len2; j++) {
					char c2;

					c2 = word2[j-1];
					if (c1 == c2) {
							matrix[i][j] = matrix[i-1][j-1];
					}
					else {
							int delete;
							int insert;
							int substitute;
							int minimum;

							delete = matrix[i-1][j] + 1;
							insert = matrix[i][j-1] + 1;
							substitute = matrix[i-1][j-1] + 1;
							minimum = delete;
							if (insert < minimum) {

									minimum = insert;
							}
							if (substitute < minimum) {
									minimum = substitute;
							}
							matrix[i][j] = minimum;
					}
			}
	}
	return matrix[len1][len2];
}


// inserts into subject[] at position pos
void append(char subject[], const char insert[], int pos) {
    char buf[MAXIMUM_WORD_LEN] = {}; // 100 so that it's big enough. fill with 0
    // or you could use malloc() to allocate sufficient space

    strncpy(buf, subject, pos); // copy at most first pos characters
    int len = strlen(buf);
    strcpy(buf+len, insert); // copy all of insert[] at the end
    len += strlen(insert);  // increase the length by length of insert[]
    strcpy(buf+len, subject+pos); // copy the rest

    strcpy(subject, buf);   // copy it back to subject
    // deallocate buf[] here, if used malloc()
		
}

//delete a char from different positions and then add the edit that apears
//first in the dictionary to hashtable for edits
void delete(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);

	//delete a char
	for(int i = 0; i < len; i++){
		strcpy(temp, head);
		memmove(&temp[i], &temp[i+1], len- i);
		int one_distance_key = xor_hash(temp, hashtable.nslots);

		Bucket* head = hashtable.lists[one_distance_key].head;
		// go through the hashtable for dictionary to find the edit
		while(hashtable.lists[one_distance_key].head){
			if(strcmp(hashtable.lists[one_distance_key].head->key, temp) == 0){

				//find the match that has lowesr position in dictionary
				if(min_value ==0){
					min_value = hashtable.lists[one_distance_key].head->value;
					min_str = hashtable.lists[one_distance_key].head->key;
				}
				else if(hashtable.lists[one_distance_key].head->value < min_value){
					min_value = hashtable.lists[one_distance_key].head->value;
					min_str = hashtable.lists[one_distance_key].head->key;
				}

			}
			hashtable.lists[one_distance_key].head = hashtable.lists[one_distance_key].head->next;
		}
		hashtable.lists[one_distance_key].head = head;

	}
	//add the edit to the hashtable for edits
	list_t_add_start(&hashtable_edits.lists[hash_value], min_str, min_value);
}


//                * * * finding one edit away chars * * *

//insert a char at different positions and then add the edit that apears
//first in the dictionary, to hashtable for edits
void insert(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);

	//add a char
	for(int i = 0; i < len+2; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			append(temp, &l , i);
			int one_distance_key = xor_hash(temp, hashtable.nslots);

			// go through the hashtable for dictionary to find the edit
			Bucket* head = hashtable.lists[one_distance_key].head;
			while(hashtable.lists[one_distance_key].head){
				if(strcmp(hashtable.lists[one_distance_key].head->key, temp) == 0){
					//find the match that has lowesr position in dictionary
					if(min_value ==0){
						min_value = hashtable.lists[one_distance_key].head->value;
						min_str = hashtable.lists[one_distance_key].head->key;
					}
					else if(hashtable.lists[one_distance_key].head->value < min_value){
						min_value = hashtable.lists[one_distance_key].head->value;
						min_str = hashtable.lists[one_distance_key].head->key;
					}
				}
				hashtable.lists[one_distance_key].head = hashtable.lists[one_distance_key].head->next;
			}
			hashtable.lists[one_distance_key].head = head;
		}
	}
	//add the edit to the hashtable for edits
	list_t_add_start(&hashtable_edits.lists[hash_value], min_str, min_value);

}

//change a char in different position to a new char and then add the edit
//that apears first in the dictionary to hashtable for edits
void substitution(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);

	// subsitute chars one by one
	for(int i = 0; i < len; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			temp[i] = l;
			int one_distance_key = xor_hash(temp, hashtable.nslots);

			// go through the hashtable for dictionary to find the edit
			Bucket* head = hashtable.lists[one_distance_key].head;
			while(hashtable.lists[one_distance_key].head){
				if(strcmp(hashtable.lists[one_distance_key].head->key, temp) == 0){
					//find the match that has lowesr position in dictionary
					if(min_value ==0){
						min_value = hashtable.lists[one_distance_key].head->value;
						min_str = hashtable.lists[one_distance_key].head->key;
					}
					else if(hashtable.lists[one_distance_key].head->value < min_value){
						min_value = hashtable.lists[one_distance_key].head->value;
						min_str = hashtable.lists[one_distance_key].head->key;
					}
				}
				hashtable.lists[one_distance_key].head = hashtable.lists[one_distance_key].head->next;
			}
			hashtable.lists[one_distance_key].head = head;
		}
	}
	//add the edit to the hashtable for edits
	list_t_add_start(&hashtable_edits.lists[hash_value], min_str, min_value);
}


//                * * * finding two edit away chars * * *

//delete a char from different positions and then repeat it again and then add
//the edit that apears first in the dictionary to hashtable for edits
void two_deletes(char *head, HashTable hashtable, HashTable hashtable_edits,
	int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	//delete a char
	for(int i = 0; i < len; i++){
		strcpy(temp, head);
		memmove(&temp[i], &temp[i+1], len- i);
		char *two_distance = malloc(MAXIMUM_WORD_LEN);

		// delete another char from string
		delete(temp, hashtable, hashtable_edits, hash_value, two_distance, min_value, min_str);
		free(two_distance);
	}


}

//change a char in different position to a new char and repeat it again and
//then add the edit that apears first in the dictionary, to hashtable for edits
void two_substitutions(char *head, HashTable hashtable, HashTable hashtable_edits,
	int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			temp[i] = l;
			char *two_distance = malloc(MAXIMUM_WORD_LEN);
			substitution(temp, hashtable, hashtable_edits, hash_value, two_distance, min_value, min_str);
			free(two_distance);
		}
	}
}

//insert a char at different positions and then repeat it again then add the edit
//that apears the edit that apears first in the dictionary, to hashtable for edits
void two_inserts(char *head, HashTable hashtable, HashTable hashtable_edits,
	int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len+2; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			append(temp, &l , i);
			char *two_distance = malloc(MAXIMUM_WORD_LEN);
			insert(temp, hashtable, hashtable_edits, hash_value, two_distance, min_value, min_str);
			free(two_distance);
		}
	}

}

//insert a char at different positions and then change a char from each
// already  changed strings, then add the edit that apears first in
//the dictionary, to hashtable for edits
void insert_subsitute(char *head, HashTable hashtable, HashTable hashtable_edits,
	int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len+2; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			append(temp, &l , i);
			char *two_distance = malloc(MAXIMUM_WORD_LEN);
			substitution(temp, hashtable, hashtable_edits, hash_value, two_distance, min_value, min_str);
			free(two_distance);
		}
	}
}

//delete a char from different positions and then change a char from each strings
//then add the edit that apears first in the dictionary, to hashtable for edits
void delete_subsitute(char *head, HashTable hashtable, HashTable hashtable_edits,
	int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		strcpy(temp, head);
		memmove(&temp[i], &temp[i+1], len- i);
		char *two_distance = malloc(MAXIMUM_WORD_LEN);
		substitution(temp, hashtable, hashtable_edits, hash_value, two_distance, min_value, min_str);
		free(two_distance);
	}
}

//                * * * finding three edit away chars * * *

//delete a char from different positions and then repeat it twice more
//for each strings then add the edit that apears first in the dictionary,
// to hashtable for edits
void three_delete(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		strcpy(temp, head);
		memmove(&temp[i], &temp[i+1], len- i);
		char *three_distance = malloc(MAXIMUM_WORD_LEN);
		two_deletes(temp, hashtable, hashtable_edits, hash_value, three_distance, min_value, min_str);
		free(three_distance);
	}
}

//change a char in different position to a new char and repeat it twice more
//for each string then add the edit that apears first in the dictionary,
// to hashtable for edits
void three_substitution(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			temp[i] = l;
			char *three_distance = malloc(MAXIMUM_WORD_LEN);
			two_substitutions(temp, hashtable, hashtable_edits, hash_value,
				 three_distance, min_value, min_str);

			free(three_distance);
		}
	}

}

//insert a char to different positions and then repeat it twice more
//for each strings then add the edit that apears first in the dictionary,
// to hashtable for edits
void three_insert(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len+2; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			append(temp, &l , i);
			char *three_distance = malloc(MAXIMUM_WORD_LEN);
			two_inserts(temp, hashtable, hashtable_edits, hash_value, three_distance, min_value, min_str);
			free(three_distance);
		}
	}
}

//change a char in different position to a new char and repeat it twice more
//and then delete a char from different positions then add the edit
//that apears first in the dictionary, to hashtable for edits
void delete_sub_sub(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		strcpy(temp, head);
		memmove(&temp[i], &temp[i+1], len- i);
		char *three_distance = malloc(MAXIMUM_WORD_LEN);
		two_substitutions(temp, hashtable, hashtable_edits, hash_value, three_distance, min_value, min_str);
		free(three_distance);
	}
}

//delete a char from different positions and repeat it again then change a char
//from each strings then add the edit that apears first in the dictionary,
//to hashtable for edits
void delete_delete_sub(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			temp[i] = l;
			char *three_distance = malloc(MAXIMUM_WORD_LEN);
			two_deletes(temp, hashtable, hashtable_edits, hash_value, three_distance, min_value, min_str);
			free(three_distance);
		}
	}
}

//change a char in different position to a new char and repeat it twice more
//insert a char to different positions then add the edit that apears first
// in the dictionary, to hashtable for edits
void insert_sub_sub(char *head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len+2; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			append(temp, &l , i);
			char *three_distance = malloc(MAXIMUM_WORD_LEN);
			two_substitutions(temp, hashtable, hashtable_edits, hash_value, three_distance, min_value, min_str);
			free(three_distance);
		}
	}
}

//insert a char to different positions and repeat it again then change a char
//from each strings then add the edit that apears first in the dictionary,
//to hashtable for edits
void insert_insert_sub(char *head, HashTable hashtable, HashTable hashtable_edits,
	int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);
	for(int i = 0; i < len; i++){
		for( char l = 'a'; l<='z'; ++l) {
			strcpy(temp, head);
			temp[i] = l;
			char *three_distance = malloc(MAXIMUM_WORD_LEN);
			two_inserts(temp, hashtable, hashtable_edits, hash_value, three_distance, min_value, min_str);
			free(three_distance);
		}
	}
}

//checking through the dictionary to find a char
void check_dictionary(char *head, int edit_dist, List *dictionary ,
	 Node* dictionary_head, HashTable hashtable, HashTable hashtable_edits,
	 int hash_value, char *temp, int min_value ,char * min_str){
	int len = strlen(head);

	while(dictionary->head){
		int len_dic = strlen(((char *)dictionary->head->data));
		if (edit_distance(((char *)dictionary->head->data), head, len_dic, len) == edit_dist){
			int hash_code = xor_hash(((char *)dictionary->head->data), hashtable.nslots);
			Bucket *hash_head = hashtable.lists[hash_code].head;
			while(hashtable.lists[hash_code].head){
				if(strcmp(hashtable.lists[hash_code].head->key, ((char *)dictionary->head->data)) == 0){
					list_t_add_start(&hashtable_edits.lists[hash_value],
						 hashtable.lists[hash_code].head->key, hashtable.lists[hash_code].head->value);

				}
				hashtable.lists[hash_code].head = hashtable.lists[hash_code].head->next;
			}
			hashtable.lists[hash_code].head = hash_head;
		}
		//go to the next node
		dictionary->head= dictionary->head->next;
	}
	dictionary->head = dictionary_head;

	Bucket *edit_hashtable_head = hashtable_edits.lists[hash_value].head;
	while(hashtable_edits.lists[hash_value].head){

		if(min_value ==0){
				min_value = hashtable_edits.lists[hash_value].head->value;
				min_str = hashtable_edits.lists[hash_value].head->key;
			}
			else if(hashtable_edits.lists[hash_value].head->value < min_value){
				min_value = hashtable_edits.lists[hash_value].head->value;
				min_str = hashtable_edits.lists[hash_value].head->key;
			}

			hashtable_edits.lists[hash_value].head = hashtable_edits.lists[hash_value].head->next;
	}
	hashtable_edits.lists[hash_value].head = edit_hashtable_head;


	if(min_str != NULL){
		printf("%s\n", min_str);
	}
	if(edit_hashtable_head != NULL){
		free_bucket(edit_hashtable_head);
	}


}

//collecting all one edit distance away edits and find the one that apears first
//in dictionary and print it
void one_editdistance(char *head, List *dictionary, HashTable hashtable,
	 HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str){
	//deletion of single letter: making words 1 edit from "word"
	delete(head, hashtable, hashtable_edits, hash_value, temp, min_value, min_str);
	insert(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
	//substituting a single letter in word
	substitution(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);

	while(hashtable_edits.lists[hash_value].head){
		if(min_value ==0){
			min_value = hashtable_edits.lists[hash_value].head->value;
			min_str = hashtable_edits.lists[hash_value].head->key;
		}
		else if(hashtable_edits.lists[hash_value].head->value < min_value){
			min_value = hashtable_edits.lists[hash_value].head->value;
			min_str = hashtable_edits.lists[hash_value].head->key;
		}

		hashtable_edits.lists[hash_value].head = hashtable_edits.lists[hash_value].head->next;
	}

	if(min_str != NULL){
		printf("%s\n", min_str);
	}

}

//collecting all two edit distance away edits and find the one that apears first
//in dictionary and print it
void two_editdistance(char *head, List *dictionary, Node* dictionary_head,
	HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp,
	int min_value ,char * min_str){
	int len = strlen(head);
	//calculating the number of edits we can make by different operations
	// 2 deletes : (pow(len,2)+len)/2
	//2 insert && 2 subsitutes : pow(27,2)*2*(pow(len,2)+len+1)
	//insert + sub : pow(len+1,2)*pow(27,2)
	//del + sub: n*(n-1)*27

	//if the number of total edits mades is less than size of dictionary its efficient to do it
	if(pow(27,2)*2*(pow(len,2)+len+1)+((pow(len,2)+len)/2) + pow(len+1,2)*pow(27,2)+ len*(len-1)*27 < dictionary->size){

		two_deletes(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		two_substitutions(head, hashtable, hashtable_edits, hash_value, temp, min_value, min_str);
		two_inserts(head, hashtable, hashtable_edits, hash_value, temp, min_value, min_str);

		insert_subsitute(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		delete_subsitute(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);

		//go through the hashtable for edits and find the edit
		//that comes first in dictionary
		Bucket *hashtable_head = hashtable_edits.lists[hash_value].head;
		while(hashtable_edits.lists[hash_value].head){
			if(min_value ==0){
					min_value = hashtable_edits.lists[hash_value].head->value;
					min_str = hashtable_edits.lists[hash_value].head->key;
				}
				else if(hashtable_edits.lists[hash_value].head->value < min_value){
					min_value = hashtable_edits.lists[hash_value].head->value;
					min_str = hashtable_edits.lists[hash_value].head->key;
				}
				hashtable_edits.lists[hash_value].head = hashtable_edits.lists[hash_value].head->next;
		}
		hashtable_edits.lists[hash_value].head = hashtable_head;

		if(min_str != NULL){
			printf("%s\n", min_str);
		}
		if(hashtable_head != NULL){
			free_bucket(hashtable_head);
		}

	}
	//if the number of total edits mades is more than size of dictionary its
	//more efficient to just check through the dictionary
	else{
		check_dictionary(head, TWO_EDITDISTANCE,dictionary, dictionary_head,
			 hashtable, hashtable_edits, hash_value, temp, min_value ,min_str);
	}
}

//collecting all three edit distance away edits and find the one that apears first
//in dictionary and print it
void three_editdistance(char *head, List *dictionary, Node* dictionary_head,
	 HashTable hashtable, HashTable hashtable_edits, int hash_value,
	 char *temp, int min_value ,char * min_str){
	int len = strlen(head);

	//calculating the number of edits we can make by different operations
	// 3 deletes: n*(n-1)*(n-2)= n^3 -3n^2 +2n
	// 3 substitute: n^3*27^3
	//3 insert : (n+1)27 *(n+2)*27 *(n+3)*27
	// del + 2 sub: n* 27^2 * (n-1)^2
	// 2 del + sub: n*(n-1)*(n-2)*27
	// insert+ 2 sub: (n+1)*27*(n+1)^2*27^2
	// 2 insert + sub:(n+1)(n+2)*27^2*(n+2)*27
	int del_3 = pow(len,3)-3*pow(len,2)+2*len;
	int sub_3 = pow(len, 3)*pow(27, 3);
	int insert_3 = pow(27, 3) * (pow(len, 3) +6*pow(len, 2) + 11*len +6);
	int del_sub_2 = pow(27, 2)*(pow(len, 3) -2*pow(len, 2) + len);
	int del_2_sub = (pow(len,3)-3*pow(len,2)+2*len)*27;
	int ins_sub_2 = pow(27, 3)*pow(len+1, 3);
	int ins_2_sub = pow(27, 3)*(pow(len, 3) +5*pow(len, 2) + 8*len +4);

	//if the number of total edits mades is less than size of dictionary its efficient to do it
	if(del_3 + sub_3 + insert_3 + del_sub_2 + del_2_sub + ins_sub_2 + ins_2_sub < dictionary->size) {

		//making all the 3 dit distance away edits and add them to the hashtbale for edits
		three_delete(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		three_substitution(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		three_insert(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		delete_sub_sub(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		delete_delete_sub(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		insert_sub_sub(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);
		insert_insert_sub(head, hashtable, hashtable_edits, hash_value, temp, min_value , min_str);

		Bucket *hashtable_head = hashtable_edits.lists[hash_value].head;
		//go through the hashtable for edits and find the edit
		//that comes first in dictionary
		while(hashtable_edits.lists[hash_value].head){
			if(min_value ==0){
					min_value = hashtable_edits.lists[hash_value].head->value;
					min_str = hashtable_edits.lists[hash_value].head->key;
				}
				else if(hashtable_edits.lists[hash_value].head->value < min_value){
					min_value = hashtable_edits.lists[hash_value].head->value;
					min_str = hashtable_edits.lists[hash_value].head->key;
				}
				hashtable_edits.lists[hash_value].head = hashtable_edits.lists[hash_value].head->next;
		}
		hashtable_edits.lists[hash_value].head = hashtable_head;

		if(min_str != NULL){
			printf("%s\n", min_str);
		}
		if(hashtable_head != NULL){
			free_bucket(hashtable_head);
		}

	}
	//if the number of total edits mades is more than size of dictionary its
	//more efficient to just check through the dictionary
	else{
		check_dictionary(head, THREE_EDITDISTANCE, dictionary, dictionary_head,
			hashtable, hashtable_edits, hash_value, temp, min_value ,min_str);
	}

}
