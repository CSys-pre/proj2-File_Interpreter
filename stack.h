#ifndef STACK_H
#define STACK_H

/* this an implementation of simple Stack in C
 */

typedef struct Stack_Node {
    char data;
    struct Stack_Node* next;
    struct Stack_Node* previous;
} Stack_Node;

typedef struct Stack Stack;

Stack* Stack_new();

Stack_Node* Stack_create_node();

void Stack_push_node( Stack* stack, Stack_Node* node );
void Stack_push_data( Stack* stack, char data );

Stack_Node* Stack_pop_node(Stack* stack);
char Stack_pop_data(Stack* stack);

void Stack_clean(Stack* stack);

#endif // STACK_H
