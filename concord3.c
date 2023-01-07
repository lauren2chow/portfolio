/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Fall 2022.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"

void print_word(node_t *node, void *arg){
    /*
    The function print_word takes two parameters and prints out the text of the given node_t 
        node in the give format.
    Parameters: *node - pointer to the node_t node that you want to print the text of
                *arg - pointer to the format of the output 
    Returns: None
    */
    char *format = (char *)arg;
    printf(format, node->text);
}

void print_words(node_s *node, void *arg){
    /*
    The function print_words takes two parameters and prints out the lines of the given 
        node_s node in the give format buy calling the print_word function to print the lines.
    Parameters: *node - pointer to the node_s node that you want to print the node_t lines of
                *arg - pointer to the format of the output 
    Returns: None
    */
    char *format = (char *)arg;
    apply(node->lines, print_word, format);
}

void lower_cased(char *word, char *word_to_lower){
    /*
    The function lower_cased takes two parameters and lowercases all the letters in given word
        and assigns the result to word_to_lower 
    Parameters: *word - pointer to the word that is to be lowercased
                *word_to_lower - the result of lowering the letters in word
    Returns: None
    */
    int n = strlen(word);
    for (int i = 0 ;i < n; i++){
       word_to_lower[i] = tolower(word[i]);
    }
}


void upper_cased(char *word, char *word_to_upper){
    /*
    The function upper_cased takes two parameters and uppercases all the letters in given word
        and assigns the result to word_to_upper
    Parameters: *word - pointer to the word that is to be uppercased
                *word_to_lower - the result of uppering the letters in word
    Returns: None
    */
    int n = strlen(word);
    for (int i = 0 ;i < n; i++){
       word_to_upper[i] = toupper(word[i]);
    }
}

int version_check(char *version){
    /*
    The function version_check takes one parameters and checks to see if the version is the 
        version. If not it prints an error message and returns the 0 integer
    Parameters: *version - pointer the string containing the version of the file
    Returns: 1 - if version is correct
             0 - if version is not of the expected version
    */
    int version_length;
    int mark;
    version_length = strlen(version);
    
    if (strcmp(version, "2\n") != 0){
        if (version[version_length -1] == '\n'){
            version[version_length -1] = '\0';
        }
        printf("Input is version %s, concord3 expected version 2\n", version);
        return (mark = 0);
    }
    return (mark = 1);
}

void format_line(char *line_temp, char *indexed_word, int index, char *result){
    /*
    The function format_line takes four parameters and has 3 main parts when going through all the
        individual words in line_temp:
        1. Takes the words that appear before the index word that fits between column 10 and 30
            and appends the word to the result string
        2. Once interated to the indexed_word the function will call the upper_cased function on
            the indexed_word and append it to the result string. Then adds bank space to the front
            of string if needed to make the indexed_word start at index 30.
        3. Appends the words that appear after the index word that don't go past column 60 to 
            the result string
    Parameters: *line_temp - pointer to the line that is to be formatted
                *indexed_word - the lowered index word 
                index - the index of the first character in the index word 
                *result - string that will contain the formatted line when function is finished
    Returns: None
    */
    int marker = 1;
    char temp[70];
    char ten_space[10] = "         ";
    char one_space[1] = " ";
    char uppered[70];
    char token_lowered[100];
    char line[100];

    strncpy(line, line_temp, 100);
    char * token2 = strtok(line, "\n ");
    strncat(result, ten_space, 10);

    /* while loop going through all the words in line*/
    while (token2 != NULL){
        strncpy(token_lowered, "", 70);
        lower_cased(token2, token_lowered);

        /* if statement that performs part 3 after the indexed_word has been passed*/
        if(marker == 0){
            index = index + strlen(token2)+1;
            if (index > 50){
                return;
            }else{
                strncat(result, one_space, 1);
                strncat(result, token2, 70);
            }
        }
        /* else if statement that performs part 2 when the token_2 equals the indexed_word*/
        else if (strcmp(token_lowered,indexed_word) ==0){
            while (index < 20){
                strncpy(temp, result, 70);
                strncpy(result, "", 70);
                strncpy(result, one_space, 1);
                strncat(result, temp, 70);
                index = index + 1;
            }
            upper_cased(token2, uppered);
            strncat(result, uppered, 70);
            marker = 0;
            index = index + strlen(token2) -1;

        }
        /*the else if and else statement that performs part 1 when the indexed_word has yet 
            to be passed*/
        else if (index <=20){
            strncat(result, token2,70);
            strncat(result, one_space,1);
        }else{
            index = index - (strlen(token2)+1);
        }
        token2 = strtok(NULL, "\n ");
    }
}


node_t *add_nonindex_list(node_t *nonindex_list, char *line){
	/*
    The function add_nonindex_list takes two parameters and creates a new node_t node that 
        contains the line given and adds the new node inorder to the node_t linked list given
    Parameters: *nonindex_list - pointer to the head of the node_t list that the new node will
                    added to
                *line - the string that the new node will contain
    Returns: node_t - a pointer to the head of the linked list with the new node added
    */
    int line_length;
    char lowered_exclude[40] = "";
    lower_cased(line, lowered_exclude);
    line_length = strlen(line);

    if (lowered_exclude[line_length-1] == '\n'){
            lowered_exclude[line_length -1] = '\0';
    }
    nonindex_list = add_end(nonindex_list,new_node(lowered_exclude));
    return nonindex_list;
}


node_s *add_index_list(node_s *index_list, char *line, node_t *nonindex_list){
    /*
    The function add_index_list takes three parameters and add_inorders the created new node_s node that 
        contains the index word and a node_t linked list of the formated lines of the index word
    Parameters: *index_list - the linked list containing the key word and an array of the formatted 
                    lines of the index word
                *line - pointer to the line that is to be formatted
                *nonindex_list - pointer to the head of the nonindex words linked list
    Returns: node_s - a pointer to the head of the linked list with the new node added  
    */
    int inexclude = 0;
    char line_temp[100];
    int index_iw = 0;
    char lowered[100];
    char result[70];
    char* context = NULL;
    node_t *curr; 

    strncpy(line_temp, line, 100);
    char * token = strtok_r(line, "\n ", &context);
    while(token != NULL){
        strncpy(lowered, "", 100);
        lower_cased(token, lowered);
        for (curr = nonindex_list; curr != NULL; curr = curr->next){             
            if (strncmp(curr->text, lowered, 100)==0){
                inexclude = 1;
                break;
            }
        }
        if (inexclude == 0){
            strncpy(result, "", 70);
            format_line(line_temp, lowered, index_iw, result);
            index_list = add_inorders(index_list, new_nodes(lowered, result));
        }
        inexclude = 0;
        index_iw = index_iw + strlen(token) + 1;
        token = strtok_r(NULL, "\n ", &context);
    }
    index_iw = 0;
    return index_list;
}

void free_list(node_t *head){
    /*
    The function free_list takes one parameter and frees the linked list of the given node_t
    Parameters: *head - pointer to the head of the linked list to be freed
    Returns: None
    */
    node_t *temp_node = NULL;
    temp_node = head;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        head = remove_front(head);
        free(temp_node);
        temp_node = head;
    }
}

void free_lists(node_s *head){
    /*
    The function free_lists takes one parameter and frees the linked list of the given node_s
    Parameters: *head - pointer to the head of the linked list to be freed
    Returns: None
    */
    node_s *temp_node = NULL;
    temp_node = head;
    while (temp_node != NULL) {
        free_list(temp_node->lines);
        assert(temp_node != NULL);
        head = remove_fronts(head);
        free(temp_node);
        temp_node = head;
    }
}

int main(int argc, char *argv[]){
    /*
    Takes input from stdin and prints formatted strings with the uppercase indexed word from stdin and correct indexing(indexed word 
		is left-aligned, key word begins at the 30th column of the returned string, words on the 
		left of the index word do not go past column 10 and the words to the right of the indexed
		word don't go further right than column 60).
    */
    node_t *nonindex_list = NULL;
    node_s *index_list = NULL;
    
    char *line = NULL;
	size_t len = 0;
	ssize_t read;
    getline(&line, &len, stdin);
    if (version_check(line) == 0){
        exit(1);
    }
    getline(&line, &len, stdin);
    read = getline(&line, &len, stdin);
	while (read !=-1){
        
        if (strncmp(line, "\"\"\"\"\n", 40) == 0){
            break;
        }
        nonindex_list = add_nonindex_list(nonindex_list, line);
        read = getline(&line, &len, stdin);
	}

    getline(&line, &len, stdin);
    while(read != -1){
        index_list = add_index_list(index_list, line, nonindex_list);
        read = getline(&line, &len, stdin);
    }

    free(line);
    
    
    applys(index_list, print_words, "%s\n");
    free_lists(index_list);
    free_list(nonindex_list);
    
	exit(0);

}
