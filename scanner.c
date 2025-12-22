#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN         64
#define MAX_FILENAME    256

int main(const int argc, char **argv)
{
        FILE *in, *out;
        int ch, next, idx;
        char buffer[MAX_LEN], *output_file;

        if (argc < 2)
                return fprintf(stderr, "no input files.\n");

        in = fopen(argv[1], "r");
        if (!in)
                return fprintf(stderr, "cannot open input file.\n");

        output_file = argv[1];
        strcat(output_file, ".token");
        out = fopen(output_file, "w");
        if (!out)
                return fprintf(stderr, "cannot open output file.\n");

        while ((ch = fgetc(in)) != EOF) {
                if (isspace(ch))
                        continue;

                if (isalpha(ch)) {
                        idx = 0;
                        buffer[idx++] = (char) ch;

                        while ((ch = fgetc(in)) != EOF && isalnum(ch)) {
                                buffer[idx++] = (char) ch;
                        }
                        buffer[idx] = '\0';

                        if (ch != EOF)
                                ungetc(ch, in);

                        if (strcmp(buffer, "begin") == 0)
                                fprintf(out, "(1, begin)\n");
                        else if (strcmp(buffer, "if") == 0)
                                fprintf(out, "(2, if)\n");
                        else if (strcmp(buffer, "then") == 0)
                                fprintf(out, "(3, then)\n");
                        else if (strcmp(buffer, "while") == 0)
                                fprintf(out, "(4, while)\n");
                        else if (strcmp(buffer, "do") == 0)
                                fprintf(out, "(5, do)\n");
                        else if (strcmp(buffer, "end") == 0)
                                fprintf(out, "(6, end)\n");
                        else
                                fprintf(out, "(10, '%s')\n", buffer);
                } else if (isdigit(ch)) {
                        idx = 0;
                        buffer[idx++] = (char) ch;

                        while ((ch = fgetc(in)) != EOF && isdigit(ch)) {
                                buffer[idx++] = (char) ch;
                        }
                        buffer[idx] = '\0';

                        if (ch != EOF)
                                ungetc(ch, in);

                        fprintf(out, "(11, %s)\n", buffer);
                } else {
                        switch (ch) {
                        case '+':
                                fprintf(out, "(13, +)\n");
                                break;
                        case '-':
                                fprintf(out, "(14, -)\n");
                                break;
                        case '*':
                                fprintf(out, "(15, *)\n");
                                break;
                        case '/':
                                fprintf(out, "(16, /)\n");
                                break;
                        case ':':
                                next = fgetc(in);
                                if (next == '=') {
                                        fprintf(out, "(18, :=)\n");
                                } else {
                                        fprintf(out, "(17, :)\n");
                                        if (next != EOF)
                                                ungetc(next, in);
                                }
                                break;
                        case '<':
                                next = fgetc(in);
                                if (next == '=') {
                                        fprintf(out, "(22, <=)\n");
                                } else if (next == '>') {
                                        fprintf(out, "(21, <>)\n");
                                } else {
                                        fprintf(out, "(20, <)\n");
                                        if (next != EOF)
                                                ungetc(next, in);
                                }
                                break;
                        case '>':
                                next = fgetc(in);
                                if (next == '=') {
                                        fprintf(out, "(24, >=)\n");
                                } else {
                                        fprintf(out, "(23, >)\n");
                                        if (next != EOF)
                                                ungetc(next, in);
                                }
                                break;
                        case '=':
                                fprintf(out, "(25, =)\n");
                                break;
                        case ';':
                                fprintf(out, "(26, ;)\n");
                                break;
                        case '(':
                                fprintf(out, "(27, ()\n");
                                break;
                        case ')':
                                fprintf(out, "(28, ))\n");
                                break;
                        case '#':
                                fprintf(out, "(0, #)\n");
                                fclose(in);
                                fclose(out);
                                return 0;
                        default:
                                break;
                        }
                }
        }

        fclose(in);
        fclose(out);

        return 0;
}