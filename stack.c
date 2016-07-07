#include "stack.h"
#include <assert.h>
#include <stdlib.h>

static Stack_Node* start_node;
static Stack_Node* end_node;

// acts like constructor
void Stack_init()
{
    start_node = NULL;
    end_node   = NULL;
}

Stack_Node* Stack_create_node()
{
    Stack_Node* node = malloc( sizeof(Stack_Node) );
    node->next = NULL;

    return node;
}

void Stack_push_node( Stack_Node* node )
{
    // handle start and end pointers
    if( start_node == NULL )
        start_node = node;

    end_node = node;
}

void Stack_push_data( char data )
{
    // create new node
    Stack_Node* node = Stack_create_node();

    // append data
    node->data = data;

    // push the new node
    Stack_push_node( node );
}

// acts like destructor
void Stack_clean()
{

}
