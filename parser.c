#include "rd.h"

int main(const int argc, char *argv[])
{
        if (argc != 2)
                return fprintf(stderr, "error\n");

        in = fopen(argv[1], "r");
        if (!in)
                return fprintf(stderr, "error\n");

        next_token();
        program();

        if (lookahead != TK_EOF)
                error_flag = 1;

        if (error_flag)
                printf("error\n");
        else
                printf("success\n");

        fclose(in);

        return 0;
}