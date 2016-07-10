#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H

#include <stdint.h>

// this function call once
void ITP_init();

// convert from infix to postfix
char* ITP_convert( const char* infix );

void ITP_clean();

#endif // INFIXTOPOSTFIX_H
