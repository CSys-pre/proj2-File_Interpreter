#ifndef STACK_H
#define STACK_H

/* this an implementation of simple Stack in C
 */

// the nodes that occupy stack(s)
typedef struct Stack_Node {
    char data;
    struct Stack_Node* next;
    struct Stack_Node* previous;
} Stack_Node;

// struct that represent Stack
// it's body is hidden to secure data
typedef struct Stack Stack;

// create new stack
Stack* Stack_new();

// create new node in stack
Stack_Node* Stack_create_node();

// push node/data
void Stack_push_node( Stack* stack, Stack_Node* node );
void Stack_push_data( Stack* stack, char data );

// pop node/data
Stack_Node* Stack_pop_node(Stack* stack);
char Stack_pop_data(Stack* stack);

// clean up
void Stack_clean(Stack* stack);

#endif // STACK_H
