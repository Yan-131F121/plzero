#include "rd.h"

int main(const int argc, char *argv[])
{
        token_t tp;

        if (argc != 2)
                return fprintf(stderr, "error\n");

        tp.in = fopen(argv[1], "r");
        if (!tp.in)
                return fprintf(stderr, "error\n");

        tp.error_flag = 0;
        next_token(&tp);
        program(&tp);

        if (tp.lookahead != TK_EOF)
                tp.error_flag = 1;

        if (tp.error_flag)
                printf("error\n");
        else
                printf("success\n");

        fclose(tp.in);

        return 0;
}