#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//static Stack_Node* start_node;
//static Stack_Node* end_node;

struct Stack{
    Stack_Node* start_node;
    Stack_Node* end_node;
};

// acts like constructor
Stack* Stack_new()
{
    Stack *new_stack = malloc( sizeof(Stack) );

    new_stack->start_node = NULL;
    new_stack->end_node   = NULL;

    return new_stack;
}

Stack_Node* Stack_create_node()
{
    Stack_Node* node = malloc( sizeof(Stack_Node) );
    node->previous = NULL;
    node->next = NULL;

    return node;
}

void Stack_push_node( Stack* stack, Stack_Node* node )
{

    // handle start pointer
    if( stack->start_node == NULL )
        stack->start_node = node;

    else
    {
        // prevoius -> previous node, next -> NULL
        node->previous = stack->end_node;
        stack->end_node->next = node;
    }

    // update end pointer
    stack->end_node = node;
}

void Stack_push_data( Stack* stack, char data )
{
    // create new node
    Stack_Node* node = Stack_create_node();

    // append data
    node->data = data;

    // push the new node
    Stack_push_node( stack, node );
}

Stack_Node* Stack_pop_node(Stack* stack)
{
    // check if there is no nodes left
    if( stack->end_node == NULL )
    {
        fprintf(stderr, "Empty Stack\n");
        return NULL;
    }

    Stack_Node* node = stack->end_node;

    // update pointers to remove the node from the stack
    stack->end_node = node->previous;
    // check if this is not the last node
    if( node->previous != NULL )
        stack->end_node->next = NULL;

    return node;
}

char Stack_pop_data(Stack* stack)
{
    Stack_Node* node = Stack_pop_node( stack );

    // check if there is no nodes left
    if( node == NULL )
        return NULL;

    char data = node->data;

    // free the node memory
    free(node);

    return data;
}

// acts like destructor
void Stack_clean( Stack* stack )
{

}
