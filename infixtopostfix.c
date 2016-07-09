#include "infixtopostfix.h"

#include <stdlib.h>
#include <string.h>

static uint32_t string_to_integer( const char* str );

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
