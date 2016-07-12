/* This library take a mathematical equation as STRING, interprete it
 * and get back the answer.
 * It could also convert infix to postfix only
 * # USAGE:
 * 1- call ExpressionParser_init once to initiate the library
 * 2- call ExpressionParser_infix_to_postfix OR ExpressionParser_parse
 * 3- call ExpressionParser_clean to clean the library
 */

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <stdint.h>

// this function call once
void ExpressionParser_init();

// convert from infix to postfix
char* ExpressionParser_infix_to_postfix( const char* infix );

// it takes the infix (the expression as string)
// and return the result vaule of the expression back
uint32_t ExpressionParser_parse( const char* infix );

void ExpressionParser_clean();

#endif // EXPRESSION_PARSER_H
