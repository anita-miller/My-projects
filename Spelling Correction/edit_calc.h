/* * * * * * *
 * Module for functions that solve the coding tasks from assignment 2
 *
 * created for COMP20007 Design of Algorithms - Assignment 2, 2018
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 */

#ifndef EDIT_CALC_H
#define EDIT_CALC_H

#include "list.h"

// retrun the edit distance between 2 chars
int edit_distance(char *word1, char *word2, int len1, int len2);

// inserts into subject[] at position pos
void append(char subject[], const char insert[], int pos);

//delete a char from different positions and then add the edit that apears
//first in the dictionary to hashtable for edits
void delete(char *head, HashTable hashtable,HashTable hashtable_edits,int hash_value, char *temp, int min_value ,char * min_str);

//insert a char at different positions and then add the edit that apears
//first in the dictionary, to hashtable for edits
void insert(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//change a char in different position to a new char and then add the edit
//that apears first in the dictionary to hashtable for edits
void substitution(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//delete a char from different positions and then repeat it again and then add
//the edit that apears first in the dictionary to hashtable for edits
void two_deletes(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//change a char in different position to a new char and repeat it again and
//then add the edit that apears first in the dictionary, to hashtable for edits
void two_substitutions(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//insert a char at different positions and then repeat it again then add the edit
//that apears the edit that apears first in the dictionary, to hashtable for edits
void two_inserts(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//insert a char at different positions and then change a char from each
// already  changed strings, then add the edit that apears first in
//the dictionary, to hashtable for edits
void insert_subsitute(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//delete a char from different positions and then change a char from each strings
//then add the edit that apears first in the dictionary, to hashtable for edits
void delete_subsitute(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//delete a char from different positions and then repeat it twice more
//for each strings then add the edit that apears first in the dictionary,
// to hashtable for edits
void three_delete(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//change a char in different position to a new char and repeat it twice more
//for each string then add the edit that apears first in the dictionary,
// to hashtable for edits
void three_substitution(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//insert a char to different positions and then repeat it twice more
//for each strings then add the edit that apears first in the dictionary,
// to hashtable for edits
void three_insert(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//change a char in different position to a new char and repeat it twice more
//and then delete a char from different positions then add the edit
//that apears first in the dictionary, to hashtable for edits
void delete_sub_sub(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//delete a char from different positions and repeat it again then change a char
//from each strings then add the edit that apears first in the dictionary,
//to hashtable for edits
void delete_delete_sub(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//change a char in different position to a new char and repeat it twice more
//insert a char to different positions then add the edit that apears first
// in the dictionary, to hashtable for edits
void insert_sub_sub(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//insert a char to different positions and repeat it again then change a char
//from each strings then add the edit that apears first in the dictionary,
//to hashtable for edits
void insert_insert_sub(char *head, HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//checking through the dictionary to find a char
void check_dictionary(char *head, int edit_dist, List *dictionary, Node* dictionary_head,HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//collecting all one edit distance away edits and find the one that apears first
//in dictionary and print it
void one_editdistance(char *head, List *dictionary,HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//collecting all two edit distance away edits and find the one that apears first
//in dictionary and print it
void two_editdistance(char *head, List *dictionary, Node* dictionary_head,HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);

//collecting all three edit distance away edits and find the one that apears first
//in dictionary and print it
void three_editdistance(char *head, List *dictionary, Node* dictionary_head,HashTable hashtable, HashTable hashtable_edits, int hash_value, char *temp, int min_value ,char * min_str);



#endif
