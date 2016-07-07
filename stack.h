#ifndef STACK_H
#define STACK_H

/* this an implementation of simple Stack in C
 */

typedef struct Stack_Node {
    char data;
    struct Stack_Node* next;
    struct Stack_Node* previous;
} Stack_Node;

// acts like constructor
void Stack_init();

Stack_Node* Stack_create_node();
void Stack_push_node( Stack_Node* node );
void Stack_push_data( char data );
Stack_Node* Stack_pop_node();
char Stack_pop_data();

// acts like destructor
void Stack_clean();

#endif // STACK_H
