#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <stdint.h>

// this function call once
void ExpressionParser_init();

// convert from infix to postfix
char* ExpressionParser_infix_to_postfix( const char* infix );

void ExpressionParser_clean();

#endif // EXPRESSION_PARSER_H
