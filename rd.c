#include "rd.h"

void next_token(token_t *tp)
{
        char line[MAX_LEN];
        int code;

        if (fgets(line, MAX_LEN, tp->in) == NULL) {
                tp->lookahead = TK_EOF;
                return;
        }

        if (sscanf(line, "(%d", &code) == 1)
                tp->lookahead = code;
        else
                tp->lookahead = TK_EOF;
}

void syntax_error(token_t *tp)
{
        tp->error_flag = 1;
}

void match(token_t *tp, const int token)
{
        if (tp->lookahead == token)
                next_token(tp);
        else
                syntax_error(tp);
}

void factor(token_t *tp)
{
        if (tp->lookahead == TK_ID) {
                match(tp, TK_ID);
        } else if (tp->lookahead == TK_NUM) {
                match(tp, TK_NUM);
        } else if (tp->lookahead == TK_LP) {
                match(tp, TK_LP);
                expression(tp);
                match(tp, TK_RP);
        } else {
                syntax_error(tp);
        }
}

void item(token_t *tp)
{
        factor(tp);


LABEL_TK_MUL:
        if (tp->lookahead == TK_MUL || tp->lookahead == TK_DIV)
                goto LABEL_LOOP_ITEM;
        return;


LABEL_LOOP_ITEM:
        if (tp->lookahead == TK_MUL)
                match(tp, TK_MUL);
        else
                match(tp, TK_DIV);
        factor(tp);
        if (tp->lookahead == TK_MUL || tp->lookahead == TK_DIV)
                goto LABEL_TK_MUL;
}

void expression(token_t *tp)
{
        item(tp);


LABEL_TK_PLUS:
        if (tp->lookahead == TK_PLUS || tp->lookahead == TK_MINUS)
                goto LABEL_LOOP_EXPRESSION;
        return;


LABEL_LOOP_EXPRESSION:
        if (tp->lookahead == TK_PLUS)
                match(tp, TK_PLUS);
        else
                match(tp, TK_MINUS);

        item(tp);

        if (tp->lookahead == TK_PLUS || tp->lookahead == TK_MINUS)
                goto LABEL_TK_PLUS;
}

void assignment_statement(token_t *tp)
{
        match(tp, TK_ID);
        match(tp, TK_ASSIGN);
        expression(tp);
}

void statement(token_t *tp)
{
        assignment_statement(tp);
}

void statement_string(token_t *tp)
{
        statement(tp);


LABEL_TK_SEMI:
        if (tp->lookahead == TK_SEMI)
                goto LABEL_LOOP_STATEMENT_STRING;

        return;


LABEL_LOOP_STATEMENT_STRING:
        match(tp, TK_SEMI);

        statement(tp);

        if (tp->lookahead == TK_SEMI)
                goto LABEL_TK_SEMI;
}

void program(token_t *tp)
{
        match(tp, TK_BEGIN);
        statement_string(tp);
        match(tp, TK_END);
}