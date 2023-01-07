/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"


node_t *new_node(char *text) {
    assert( text != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));
    strncpy(temp->text, text, LIST_MAXLEN_LINE);
    temp->next = NULL;

    return temp;
}


node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}


node_s *new_nodes(char *text, char *line) {
    assert( text != NULL);
    

    node_s *temp = (node_s *)emalloc(sizeof(node_s));
    strncpy(temp->text, text, LIST_MAXLEN_TEXT);
    temp->lines = new_node(line);

    temp->next = NULL;



    return temp;
}


node_s *add_fronts(node_s *list, node_s *new) {
    new->next = list;
    
    return new;
}


node_s *add_ends(node_s *list, node_s *new) {
    node_s *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

node_s *add_inorders(node_s *list, node_s *new) {
	/*
	The function add_inorders takes two parameters and adds the new node into the
		 given node_s list in alphabetical based off of text 
    Parameters: *list - pointer to the head of node_s linked list that the new node 
    						will be added to
                *new - pointer to the new node_s that will be added to list 
    Returns: an node_s - of pointer to the head of the list with the new node added
    */
	node_s *curr = NULL;
	node_s *prev = NULL;
	
	
	if(list == NULL){
		return new;	
	}
	
	for(curr=list; curr !=NULL; curr = curr->next){
		if(strcmp(curr->text, new->text)<0){
			prev = curr;		
		}else if(strcmp(curr->text, new->text) == 0){
			curr->lines = add_end(curr->lines, new->lines);
            return list;
			
		}else {
			break;	
		}
	}
    if(prev==NULL){
        new->next = curr;
        return new;	
        }else{
            prev->next = new;
            new->next = curr;
            return list;	
        }	
    return list;
}


node_s *peek_fronts(node_s *list) {
    return list;
}


node_s *remove_fronts(node_s *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void applys(node_s *list,void (*fn)(node_s *list, void *),void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
