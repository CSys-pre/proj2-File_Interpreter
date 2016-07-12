#include "expression_parser.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_POSTFIX_SIZE 100

static uint32_t string_to_integer( const char* str, size_t len );
static uint32_t ExpressionParser_infix_to_postfix_inner(const char *infix, char* postfix );
static char* remove_spaces( char* str );
static bool check_initation();
//TODO: create a function to validate the input infix

static uint32_t __add( uint32_t num1, uint32_t num2 );
static uint32_t __sub( uint32_t num1, uint32_t num2 );
static uint32_t __mul( uint32_t num1, uint32_t num2 );
static uint32_t __div( uint32_t num1, uint32_t num2 );
static uint32_t __mod( uint32_t num1, uint32_t num2 );

// TODO: These two functions is not working
static uint32_t __shift_left( uint32_t num1, uint32_t num2 );
static uint32_t __shift_right( uint32_t num1, uint32_t num2 );

static uint32_t __and( uint32_t num1, uint32_t num2 );
static uint32_t __or( uint32_t num1, uint32_t num2 );
static uint32_t __xor( uint32_t num1, uint32_t num2 );

// type def to this pointer of function with name `ASCII_FUNC_PTR`
typedef uint32_t (*ASCII_FUNC_PTR)(uint32_t, uint32_t);

static const int8_t* ASCII_PRI = NULL;
static const ASCII_FUNC_PTR* ASCII_ADDR_ARR;
static const uint16_t ASCII_LEN = 256;

void ExpressionParser_init()
{
    // to make sure that this function called once
    if( ASCII_PRI != NULL )
        return;

    // Create ASCII table
    // we use temp here as a temporary pointer to assign the values
    // then make the table const ( by make the pointer hold it const )
    int8_t* temp = malloc( ASCII_LEN * sizeof(int8_t) );
    ASCII_FUNC_PTR* temp2 = malloc( ASCII_LEN * sizeof(ASCII_FUNC_PTR) );

    // TODO: we need to remove that part - performance
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

    // pointer of functions for operators
    temp2['*'] = __mul;
    temp2['/'] = __div;
    temp2['%'] = __mod;
    temp2['+'] = __add;
    temp2['-'] = __sub;
    temp2['>'] = __shift_right;
    temp2['<'] = __shift_left;
    temp2['&'] = __and;
    temp2['^'] = __xor;
    temp2['|'] = __or;

    ASCII_PRI = ( const int8_t* )temp;
    ASCII_ADDR_ARR = ( const ASCII_FUNC_PTR* )temp2;
}

bool check_initation()
{
    // to get sure that that `init` has been called
    if( ASCII_PRI == NULL )
    {
        #ifdef __DEBUG__
            fprintf(stderr, "`ExpressionParser_init()` function has not been called probably\n");
        #endif
            return false;
    }

    return true;
}

uint32_t string_to_integer( const char* str, size_t len )
{
    uint32_t integer = 0;
    uint32_t tens = 1;

    for (int iii = len - 1; iii >= 0; --iii)
    {
        integer += (uint32_t)(str[iii] - '0') * tens;
        tens *= 10;
    }

    return integer;
}

char* ExpressionParser_infix_to_postfix( const char* infix )
{
    if( check_initation() == false )
        return NULL;

    infix = remove_spaces( (char *)infix );

    char *postfix = malloc(MAX_POSTFIX_SIZE * sizeof(char));

    ExpressionParser_infix_to_postfix_inner( infix, postfix );

    return postfix;
}

uint32_t ExpressionParser_infix_to_postfix_inner(const char *infix, char* postfix )
{
    size_t len;

    if( strcmp(infix, "" ) != 0 )
        len = strlen(infix);

    else
        return 0;

    Stack* stack = Stack_new();

    uint32_t postfix_index = 0;

    uint32_t infix_index = 0;

    while ( infix_index < len )
    {
        // Operand
        if( infix[infix_index] >= '0' && infix[infix_index] <= '9' )
        {
            while( infix[infix_index] >= '0' && infix[infix_index] <= '9' )
            {
                postfix[postfix_index++] = infix[infix_index++];
            }

            postfix[postfix_index++] = ' ';
        }

        // Opeators
        else
        {
            if( Stack_is_empty(stack) == false )
            {
                uint8_t stack_last_element_priority = ASCII_PRI[(uint8_t)Stack_get_last_char(stack)];
                uint8_t current_operand_priority    = ASCII_PRI[(uint8_t)infix[infix_index]];

                // handle inner infix - the one between `()`
                if( infix[infix_index] == '(' )
                {
                    char *sub_infix = malloc( MAX_POSTFIX_SIZE * sizeof(char) );
                    uint32_t sub_infix_index = 0;

                    // ignore '('
                    infix_index++;

                    // gather the data between the `()`
                    while( infix[infix_index] != ')' )
                    {
                        sub_infix[sub_infix_index++] = infix[infix_index++];
                    }

                    // ignore ')'
                    infix_index++;

                    // the data between `()` is calculated as a new infix
                    // update the postfix_index
                    postfix_index += ExpressionParser_infix_to_postfix_inner( sub_infix, &postfix[postfix_index] );

                    free(sub_infix);

                    continue;
                }

                // if procedence of last element in the stack is higher than
                // that of the current element from the infix
                // note: ASCII priority is inverted ( 0 has the highest priority )
                while( stack_last_element_priority <= current_operand_priority )
                {
                    // push operator
                    postfix[postfix_index++] = Stack_pop_char( stack );

                    // add space after each operand poped out from the stack
                    postfix[postfix_index++] = ' ';

                    // TODO:
                    if( Stack_is_empty(stack) == true )
                        break;

                    stack_last_element_priority = ASCII_PRI[(uint8_t)Stack_get_last_char(stack)];
                    current_operand_priority    = ASCII_PRI[(uint8_t)infix[infix_index]];
                }
            }

            // push operator
            Stack_push_char(stack, infix[infix_index]);

            infix_index++;
        }
    }

    // may be there are some operators still on the stack
    while( Stack_is_empty(stack) == false )
    {
        // push operator
        postfix[postfix_index++] = Stack_pop_char( stack );

        // add space after each operand still needed to be poped out
        postfix[postfix_index++] = ' ';
    }

    // add the NULL termianal to the end of the postfix
    postfix[postfix_index] = '\0';

    return postfix_index;
}

uint32_t ExpressionParser_parse( const char* infix )
{
    if(check_initation() == false)
    {
        return -1;
    }

    uint32_t result = 0;

    char* postfix = malloc( MAX_POSTFIX_SIZE * sizeof(char) );
    postfix = ExpressionParser_infix_to_postfix( infix );
    size_t postfix_len = strlen( postfix );

    Stack* stack = Stack_new();

    uint32_t postfix_index = 0;

    char* token;
    size_t token_len;

    while ( postfix_index < postfix_len )
    {
        token = &postfix[postfix_index];
        token_len = 0;

        while( postfix[postfix_index] != ' ' && postfix_index != (postfix_len - 1) )
        {
            postfix_index++;
            token_len++;
        }

        // operand
        if( token[0] >= '0' && token[0] <= '9' )
        {
            Stack_push_uint32(stack, string_to_integer(token, token_len));
        }

        // operator
        else if( token[0] != ' ' && token[0] != '\0' )
        {
            char __operator = token[0];
            uint32_t num2 = Stack_pop_uint32(stack);
            uint32_t num1 = Stack_pop_uint32(stack);

            // Abracadabra :D
            result = ASCII_ADDR_ARR[(uint8_t)__operator](num1, num2);

            Stack_push_uint32(stack, result);
        }

        postfix_index++;
    }

    Stack_clean(stack);

    return result;
}

char* remove_spaces( char* str )
{
    // duplicate `str`
    char* start = strdup( str );

    if( start != NULL )
        str = start;

    else
        return NULL;

    char* next  = start;

    while( *next != '\0' )
    {
        if( *next == ' ' )
            next++;

        else
            *(start++) = *(next++);
    }

    *start = '\0';

    return str;
}

uint32_t __add( uint32_t num1, uint32_t num2 )
{
    return num1 + num2;
}

uint32_t __sub( uint32_t num1, uint32_t num2 )
{
    return num1 - num2;
}

uint32_t __mul( uint32_t num1, uint32_t num2 )
{
    return num1 * num2;
}

uint32_t __div( uint32_t num1, uint32_t num2 )
{
    return num1 / num2;
}

uint32_t __mod( uint32_t num1, uint32_t num2 )
{
    return num1 % num2;
}

uint32_t __shift_left( uint32_t num1, uint32_t num2 )
{
    return num1 << num2;
}

uint32_t __shift_right( uint32_t num1, uint32_t num2 )
{
    return num1 >> num2;
}

uint32_t __and( uint32_t num1, uint32_t num2 )
{
    return num1 & num2;
}

uint32_t __or( uint32_t num1, uint32_t num2 )
{
    return num1 | num2;
}

uint32_t __xor( uint32_t num1, uint32_t num2 )
{
    return num1 ^ num2;
}

void ExpressionParser_clean()
{
    // clean the ascii table
    free((char *)ASCII_PRI);
}
