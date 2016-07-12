/* This an implementation of simple Stack in C
 * it could handle `char` and `unsigned int` until now
 * # USAGE:
 * 1- call Stack_new to create a new stack
 * 2- push data using either `Stack_push_char` or `Stack_push_uint32` but not both.
 * 3- pop data using either `Stack_pop_char` or `Stack_pop_uint32` but not both.
 * 4- call Stack_clean to clean the created stack(s)
 *
 * NOTE: there is a macro called __DEBUG__ that can be called to show more
 * verbose messages
 */

#ifndef STACK_H
#define STACK_H

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
