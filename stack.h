#ifndef STACK_H
#define STACK_H

/* this an implementation of simple Stack in C
 */

typedef struct Stack_Node {
    char data;
    struct Stack_Node* next;
} Stack_Node;

// acts like constructor
void Stack_init();

Stack_Node* Stack_create_node();
void Stack_push( Stack_Node* node );
Stack_Node* Stack_pop();

// acts like destructor
void Stack_clean();

#endif // STACK_H
