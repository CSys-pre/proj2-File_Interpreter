#include "infixtopostfix.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

static uint32_t string_to_integer( const char* str );

static const int8_t* ASCII = NULL;
static const uint16_t ASCII_LEN = 256;

void ITP_init()
{
    // to make sure that this function called once
    if( ASCII != NULL )
        return;

    // Create ASCII table
    // we use temp here as a temporary pointer to assign the values
    // then make the table const ( by make the pointer hold it const )
    int8_t* temp = malloc( ASCII_LEN * sizeof(int8_t) );

    // assign all its members by -1 by default
    for (int iii = 0; iii < ASCII_LEN; ++iii)
    {
        memset( &temp[iii], -1, sizeof(int8_t) );
    }

    // give priority to the operators in the ASCII table
    // according to their precedence ( 0 means highest priority )
    temp['('] = 0;
    temp[')'] = 0;

    temp['*'] = 1;
    temp['/'] = 1;
    temp['%'] = 1;

    temp['+'] = 2;
    temp['-'] = 2;

    temp['>'] = 3;
    temp['<'] = 3;

    temp['&'] = 4;

    temp['^'] = 5;

    temp['|'] = 6;

    ASCII = ( const int8_t* )temp;
}

uint32_t string_to_integer( const char* str )
{
    size_t len = strlen( str );
    uint32_t integer = 0;
    uint32_t tens = 1;

    for (int iii = len - 1; iii >= 0; --iii)
    {
        integer += (uint32_t)(str[iii] - '0') * tens;
        tens *= 10;
    }

    return integer;
}

const char* infix_to_postfix( const char* infix )
{
    assert( ASCII != NULL );

    size_t len = strlen(infix);
    char *postfix = malloc(len * sizeof(char));
    bool postfix_is_empty = true;

    Stack* stack = Stack_new();
    bool stack_is_empty = true;

    uint32_t postfix_index = 0;

    for (uint32_t iii = 0; iii < len; ++iii)
    {
//        if( (stack_is_empty == false) && (postfix_is_empty == false) )
//        {
//            if(  )
//            {

//            }

//            else if(  )
//            {

//            }
//        }

//        else if( (stack_is_empty == true) && (postfix_is_empty == false) )
//        {

//        }

//        else if( (stack_is_empty == true) && (postfix_is_empty == true) )
//        {
//            //TODO: what if the user input a negative number ??
//            postfix[postfix_index] = infix[iii];
//            postfix_index++;
//        }

        // Operand
        if( infix[iii] >= '0' && infix[iii] <= '9' )
        {
            postfix[postfix_index] = infix[iii];
            postfix_index++;
        }

        // opeators
        else
        {
            if( Stack_is_empty(stack) == false )
            {
                uint8_t stack_last_element_priority = ASCII[(uint8_t)Stack_get_last(stack)];
                uint8_t current_operand_priority    = ASCII[(uint8_t)infix[iii]];

                // if procedence of last element in the stack is higher than
                // that of the current element from the infix
                // note: ASCII priority is inverted ( 0 has the highest priority )
                if( stack_last_element_priority < current_operand_priority )
                {
                    postfix[postfix_index] = Stack_pop_data( stack );
                    postfix_index++;
                }
            }

            Stack_push_data(stack, infix[iii]);
        }
    }

    while( Stack_is_empty(stack) == false )
    {
        postfix[postfix_index] = Stack_pop_data( stack );
        postfix_index++;
    }

    return postfix;
}
