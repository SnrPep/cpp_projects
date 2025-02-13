#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_nonblank = 0;
int show_ends = 0;
int number_all = 0;
int squeeze_blank = 0;
int show_tabs = 0;

void cat_file(FILE *file) {
    int c, prev = '\n';
    int line_number = 1;
    while ((c = fgetc(file)) != EOF) {
        if (squeeze_blank && c == '\n' && prev == '\n') {
            continue;
        }
        if (number_nonblank && c != '\n' && (prev == '\n' || line_number == 1)) {
            printf("%6d\t", line_number++);
        }
        if (number_all && (prev == '\n' || line_number == 1)) {
            printf("%6d\t", line_number++);
        }
        if (show_tabs && c == '\t') {
            printf("^I");
            prev = c;
            continue;
        }
        if (show_ends && c == '\n') {
            printf("$");
        }
        putchar(c);
        prev = c;
    }
}

int main(int argc, char *argv[]) {
    int i, j;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'b': number_nonblank = 1; break;
                    case 'e': show_ends = 1; break;
                    case 'n': number_all = 1; break;
                    case 's': squeeze_blank = 1; break;
                    case 't': show_tabs = 1; break;
                    default:
                        fprintf(stderr, "Unknown option: -%c\n", argv[i][j]);
                        return EXIT_FAILURE;
                }
            }
        } else {
            break;
        }
    }

    if (i == argc) {
        cat_file(stdin);
    } else {
        for (; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                perror("cat");
                return EXIT_FAILURE;
            }
            cat_file(file);
            fclose(file);
        }
    }
    return EXIT_SUCCESS;
}
