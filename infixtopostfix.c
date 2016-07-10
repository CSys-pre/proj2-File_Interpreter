#include "infixtopostfix.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

static uint32_t string_to_integer( const char* str );
static uint32_t ITP_convert_inner(const char *infix, char* postfix );

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

const char* ITP_convert( const char* infix )
{
    // to get sure that
    assert( ASCII != NULL );

    char *postfix = malloc(100 * sizeof(char));

    size_t postfix_index = ITP_convert_inner( infix, postfix );

    // add the NULL termianal to the end of the postfix
    postfix[postfix_index] = '\0';

    return postfix;
}

uint32_t ITP_convert_inner(const char *infix, char* postfix )
{
    size_t len = strlen(infix);

    bool is_operand = false;

    Stack* stack = Stack_new();

    uint32_t postfix_index = 0;

    for (uint32_t iii = 0; iii < len; ++iii)
    {
        // Operand
        if( infix[iii] >= '0' && infix[iii] <= '9' )
        {
            postfix[postfix_index++] = infix[iii];

            // as a number could consists of more that one digit
            if( is_operand == true )
                postfix[postfix_index++] = ' ';

            is_operand = true;
        }

        // Opeators
        else
        {
            if( Stack_is_empty(stack) == false )
            {
                uint8_t stack_last_element_priority = ASCII[(uint8_t)Stack_get_last(stack)];
                uint8_t current_operand_priority    = ASCII[(uint8_t)infix[iii]];

                if( infix[iii] == '(' )
                {
                    char *sub_infix = malloc( 100 * sizeof(char) );
                    uint32_t index = 0;

                    // ignore '('
                    iii++;

                    // gather the data between the `()`
                    while( infix[iii] != ')' )
                    {
                        sub_infix[index++] = infix[iii++];
                    }

                    // ignore ')'
                    iii++;

                    // the data between `()` is calculated as a new infix
                    // update the postfix_index
                    postfix_index += ITP_convert_inner( sub_infix, &postfix[postfix_index] );
                    continue;
                }

                // if procedence of last element in the stack is higher than
                // that of the current element from the infix
                // note: ASCII priority is inverted ( 0 has the highest priority )
                while( stack_last_element_priority <= current_operand_priority )
                {
                    // add space after each operand poped out from the stack
                    postfix[postfix_index++] = ' ';
                    // push operator
                    postfix[postfix_index++] = Stack_pop_data( stack );

                    stack_last_element_priority = ASCII[(uint8_t)Stack_get_last(stack)];
                    current_operand_priority    = ASCII[(uint8_t)infix[iii]];
                }
            }

            // push operator
            Stack_push_data(stack, infix[iii]);

            // add space after each operand
            postfix[postfix_index++] = ' ';

            is_operand = false;
        }
    }

    while( Stack_is_empty(stack) == false )
    {
        // push operator
        postfix[postfix_index++] = Stack_pop_data( stack );

        // add space after each operand still needed to be poped out
        postfix[postfix_index++] = ' ';
    }

    return postfix_index;
}
