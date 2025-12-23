#ifndef RD_H
#define RD_H

#include <stdio.h>

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

typedef struct {
        FILE *in;
        int lookahead;
        int error_flag;
} token_t;

void next_token(token_t *tp);

void syntax_error(token_t *tp);

void match(token_t *tp, int token);

void factor(token_t *tp);

void item(token_t *tp);

void expression(token_t *tp);

void assignment_statement(token_t *tp);

void statement(token_t *tp);

void statement_string(token_t *tp);

void program(token_t *tp);

#endif