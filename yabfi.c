#include <stdio.h>
#include <stdlib.h>

char data[30000] = {};
char *p = data;
char code[30000];
int code_length;
int current_token_index = 0;

int match_close_bracket() {
    int level = 0;
    for (int i = current_token_index + 1; i < code_length; i++)
        if (code[i] == '[') level++;
        else if (code[i] == ']')
            if (level > 0) level--;
            else return i;
    return -1;
}

int match_open_bracket() {
    int level = 0;
    for (int i = current_token_index - 1; i >= 0; i--)
        if (code[i] == ']') level++;
        else if (code[i] == '[')
            if (level > 0) level--;
            else return i;
    return -1;
}

int interpret() {
    char token;
    while (current_token_index < code_length) {
        token = code[current_token_index];
        switch (token) {
            case '>':
                ++p; break;
            case '<':
                --p; break;
            case '+':
                ++*p; break;
            case '-':
                --*p; break;
            case '.':
                putchar(*p); break;
            case ',':
                *p = getchar(); break;
            case '[':
                if (!*p) current_token_index = match_close_bracket();
                break;
            case ']':
                if (*p) current_token_index = match_open_bracket();
                break;
        }
        if (current_token_index < 0) {
            printf("Error when matching brackets\n");
            return -1;
        }
        current_token_index ++;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *f;
    if (argc != 2) {
        printf("----------------------------------------\n");
        printf("* Yet Another BrainF Interpreter\n");
        printf("* usage: %s <file>\n", argv[0]);
        printf("----------------------------------------\n");
        return 0;
    }
    f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "File %s cannot be found\n", argv[1]);
        return EXIT_FAILURE;
    }
    code_length = fread(code, 1, 30000, f);
    fclose(f);
    return interpret();
}
