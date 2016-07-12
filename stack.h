#ifndef STACK_H
#define STACK_H

/* this an implementation of simple Stack in C
 */

#include "stdint.h"

#ifndef __cplusplus
typedef uint8_t bool;
#define true  0
#define false 1
#endif

// the nodes that occupy stack(s)
typedef struct Stack_Node Stack_Node;

// struct that represent Stack
// it's body is hidden to secure data
typedef struct Stack Stack;

// create new stack
Stack* Stack_new();

// push data
void Stack_push_char( Stack* stack, char data );
void Stack_push_uint32( Stack* stack, uint32_t data );

// pop data
char Stack_pop_char(Stack* stack);
uint32_t Stack_pop_uint32(Stack* stack);

bool Stack_is_empty( Stack* stack );

// get value of last node
char Stack_get_last_char( Stack* stack );
uint32_t Stack_get_last_uint32( Stack* stack );

// clean up
void Stack_clean(Stack* stack);

#endif // STACK_H
