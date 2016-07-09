#include "infixtopostfix.h"

#include <stdlib.h>
#include <string.h>

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
