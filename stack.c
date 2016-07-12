#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//static Stack_Node* start_node;
//static Stack_Node* end_node;

// create new node in stack
static Stack_Node* Stack_create_node();
// push node
static void Stack_push_node( Stack* stack, Stack_Node* node );
// pop node
static Stack_Node* Stack_pop_node(Stack* stack);

typedef struct Stack_Node {
    struct Stack_Node* next;
    struct Stack_Node* previous;
    uint32_t data;
} Stack_Node;

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

void Stack_push_char( Stack* stack, char data )
{
    // create new node
    Stack_Node* node = Stack_create_node();

    // append data
    node->data = (int32_t)data;

    // push the new node
    Stack_push_node( stack, node );
}

void Stack_push_uint32( Stack* stack, uint32_t data )
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
        // if define __DEBUG__ and this error happen
        // it well print this error
        #ifdef __DEBUG__
            fprintf(stderr, "Empty Stack\n");
        #endif

        return NULL;
    }

    Stack_Node* node = stack->end_node;

    // update pointers to remove the node from the stack
    stack->end_node = node->previous;
    // check if this is not the last node
    if( node->previous != NULL )
        stack->end_node->next = NULL;

    // update start_node if this is the last node to pop up
    if( stack->end_node == NULL )
        stack->start_node = NULL;

    return node;
}

char Stack_pop_char(Stack* stack)
{
    Stack_Node* node = Stack_pop_node( stack );

    // check if there is no nodes left
    if( node == NULL )
        // return null
        return (char)(0);

    char data = (uint32_t)(node->data);

    // free the node memory
    free(node);

    return data;
}

uint32_t Stack_pop_uint32(Stack* stack)
{
    Stack_Node* node = Stack_pop_node( stack );

    // check if there is no nodes left
    if( node == NULL )
        // return null
        return (char)(0);

    uint32_t data = node->data;

    // free the node memory
    free(node);

    return data;
}

bool Stack_is_empty( Stack* stack )
{
    if( stack->start_node == NULL )
        return true;

    else
        return false;
}

char Stack_get_last_char( Stack* stack )
{
    return (char)stack->end_node->data;
}

uint32_t Stack_get_last_uint32( Stack* stack )
{
    return stack->end_node->data;
}

// acts like destructor
void Stack_clean( Stack* stack )
{
    // if no nodes at all
    if( stack->start_node == NULL ) return;

    // if only one node
    else if( stack->start_node == stack->end_node )
    {
        free( stack->start_node );
    }

    // if there is more than one node
    else
    {
        Stack_Node* current_node = stack->start_node->next;

        while (current_node != NULL)
        {
            // free
            free(current_node->previous);

            // go next
            current_node = current_node->next;
        }
    }

    // free stack
    free(stack);
}
