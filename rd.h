#ifndef RD_H
#define RD_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN         256

#define TK_BEGIN        1
#define TK_END          6
#define TK_ID           10
#define TK_NUM          11
#define TK_PLUS         13
#define TK_MINUS        14
#define TK_MUL          15
#define TK_DIV          16
#define TK_ASSIGN       18
#define TK_SEMI         26
#define TK_LP           27
#define TK_RP           28
#define TK_EOF          0

extern FILE *in;
extern int lookahead;
extern int error_flag;

void next_token();

void syntax_error();

void match(int token);

void factor();

void item();

void expression();

void assignment_statement();

void statement();

void statement_string();

void program();

#endif