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

// acts like destructor
void Stack_clean()
{

}
