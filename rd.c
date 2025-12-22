#include "rd.h"

FILE *in;
int lookahead;
int error_flag = 0;

void next_token()
{
        char line[MAX_LEN];
        int code;

        if (fgets(line, MAX_LEN, in) == NULL) {
                lookahead = TK_EOF;
                return;
        }

        if (sscanf(line, "(%d", &code) == 1)
                lookahead = code;
        else
                lookahead = TK_EOF;
}

void syntax_error()
{
        error_flag = 1;
}

void match(const int token)
{
        if (lookahead == token)
                next_token();
        else
                syntax_error();
}

void factor()
{
        if (lookahead == TK_ID) {
                match(TK_ID);
        } else if (lookahead == TK_NUM) {
                match(TK_NUM);
        } else if (lookahead == TK_LP) {
                match(TK_LP);
                expression();
                match(TK_RP);
        } else {
                syntax_error();
        }
}

void item()
{
        factor();


LABEL_TK_MUL:
        if (lookahead == TK_MUL || lookahead == TK_DIV)
                goto LABEL_LOOP_ITEM;
        return;


LABEL_LOOP_ITEM:
        if (lookahead == TK_MUL)
                match(TK_MUL);
        else
                match(TK_DIV);
        factor();
        if (lookahead == TK_MUL || lookahead == TK_DIV)
                goto LABEL_TK_MUL;
}

void expression()
{
        item();


LABEL_TK_PLUS:
        if (lookahead == TK_PLUS || lookahead == TK_MINUS)
                goto LABEL_LOOP_EXPRESSION;
        return;


LABEL_LOOP_EXPRESSION:
        if (lookahead == TK_PLUS)
                match(TK_PLUS);
        else
                match(TK_MINUS);

        item();

        if (lookahead == TK_PLUS || lookahead == TK_MINUS)
                goto LABEL_TK_PLUS;
}

void assignment_statement()
{
        match(TK_ID);
        match(TK_ASSIGN);
        expression();
}

void statement()
{
        assignment_statement();
}

void statement_string()
{
        statement();


LABEL_TK_SEMI:
        if (lookahead == TK_SEMI)
                goto LABEL_LOOP_STATEMENT_STRING;

        return;


LABEL_LOOP_STATEMENT_STRING:
        match(TK_SEMI);

        statement();

        if (lookahead == TK_SEMI)
                goto LABEL_TK_SEMI;
}

void program()
{
        match(TK_BEGIN);
        statement_string();
        match(TK_END);
}