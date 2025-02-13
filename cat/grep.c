#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATTERNS 100
#define MAX_PATTERN_LENGTH 256

int ignore_case = 0;
int invert_match = 0;
int count_only = 0;
int list_files = 0;
int number_lines = 0;
int no_filenames = 0;
int suppress_errors = 0;
int only_matching = 0;
char *patterns[MAX_PATTERNS];
int pattern_count = 0;

void to_lowercase(char *str) {
    for (; *str; str++) *str = tolower(*str);
}

int match_pattern(const char *line) {
    for (int i = 0; i < pattern_count; i++) {
        char temp_line[MAX_PATTERN_LENGTH], temp_pattern[MAX_PATTERN_LENGTH];
        strcpy(temp_line, line);
        strcpy(temp_pattern, patterns[i]);
        if (ignore_case) {
            to_lowercase(temp_line);
            to_lowercase(temp_pattern);
        }
        if (strstr(temp_line, temp_pattern) != NULL) {
            return 1;
        }
    }
    return 0;
}

void grep_file(FILE *file, const char *filename) {
    char line[1024];
    int line_number = 0, match_count = 0;
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        int matched = match_pattern(line);
        if (invert_match) matched = !matched;
        if (matched) {
            if (count_only) {
                match_count++;
                continue;
            }
            if (list_files) {
                printf("%s\n", filename);
                return;
            }
            if (!no_filenames && filename) {
                printf("%s:", filename);
            }
            if (number_lines) {
                printf("%d:", line_number);
            }
            if (only_matching) {
                for (int i = 0; i < pattern_count; i++) {
                    char *match = strstr(line, patterns[i]);
                    if (match) {
                        printf("%s\n", patterns[i]);
                    }
                }
            } else {
                printf("%s", line);
            }
        }
    }
    if (count_only) {
        printf("%d\n", match_count);
    }
}

void load_patterns_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        if (!suppress_errors) perror("grep");
        exit(EXIT_FAILURE);
    }
    char pattern[MAX_PATTERN_LENGTH];
    while (fgets(pattern, sizeof(pattern), file)) {
        pattern[strcspn(pattern, "\n")] = 0;
        patterns[pattern_count++] = strdup(pattern);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    int file_start = 1;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'e':
                        if (i + 1 < argc) {
                            patterns[pattern_count++] = argv[++i];
                        }
                        break;
                    case 'i': ignore_case = 1; break;
                    case 'v':
                        invert_match = 1;
                        if (i + 1 < argc && argv[i + 1][0] != '-') {
                            patterns[pattern_count++] = argv[++i];
                        }
                        break;
                    case 'c': count_only = 1; break;
                    case 'l': list_files = 1; break;
                    case 'n': number_lines = 1; break;
                    case 'h': no_filenames = 1; break;
                    case 's': suppress_errors = 1; break;
                    case 'f':
                        if (i + 1 < argc) {
                            load_patterns_from_file(argv[++i]);
                        }
                        break;
                    case 'o': only_matching = 1; break;
                    default:
                        fprintf(stderr, "Unknown option: -%c\n", argv[i][j]);
                        return EXIT_FAILURE;
                }
            }
        } else {
            file_start = i;
            break;
        }
    }

    if (pattern_count == 0 && !invert_match) {
        fprintf(stderr, "No pattern provided");
        return EXIT_FAILURE;
    }

    if (file_start == argc) {
        grep_file(stdin, NULL);
    } else {
        for (int i = file_start; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                if (!suppress_errors) perror(argv[i]);
                continue;
            }
            grep_file(file, argv[i]);
            fclose(file);
        }
    }
    return EXIT_SUCCESS;
}
