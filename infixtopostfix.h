#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H

#include <stdint.h>

// this function call once
void ITP_init();

// convert from infix to postfix
const char* ITP_convert( const char* infix );

#endif // INFIXTOPOSTFIX_H
