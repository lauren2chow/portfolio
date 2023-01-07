#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define LIST_MAXLEN_TEXT 50
#define LIST_MAXLEN_LINE 70

typedef struct node_t {
    char text[LIST_MAXLEN_LINE];

    struct node_t  *next;
} node_t;


node_t *new_node(char *);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void    apply(node_t *, void(*fn)(node_t *, void *), void *arg);


typedef struct node_s{
    char text[LIST_MAXLEN_TEXT];
    node_t *lines;

    struct node_s  *next;
}node_s;

node_s *new_nodes(char *, char *);
node_s *add_fronts(node_s *, node_s *);
node_s *add_ends(node_s *, node_s *); /*adds the new node into the given node_s list in alphabetical based off of text*/
node_s *add_inorders(node_s *, node_s *);
node_s *peek_fronts(node_s *);
node_s *remove_fronts(node_s *);
void    applys(node_s *, void(*fn)(node_s *, void *), void *arg);

#endif
