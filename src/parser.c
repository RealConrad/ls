#include "main.h"

static void illegal_option(char opt) {
    char msg1[] = "ls: illegal option -- ";
    char newline[] = "\n";
    char usage[] = "usage: ls [-lRart] [file ...]\n";
    write(2, msg1, sizeof(msg1) - 1);
    write(2, &opt, 1);
    write(2, newline, sizeof(newline) - 1);
    write(2, usage, sizeof(usage) - 1);
    exit(EXIT_FAILURE);
}

static int is_valid_option_string(const char *arg) {
    for (int j = 1; arg[j] != '\0'; j++) {
        char c = arg[j];
        if (c != 'l' && c != 'R' && c != 'a' && c != 'r' && c != 't') {
            return 0;
        }
    }
    return 1;
}

static void process_option_string(const char *arg, Options *opts) {
    for (int j = 1; arg[j] != '\0'; j++) {
        switch (arg[j]) {
            case 'l':
                opts->l_flag = 1;
                break;
            case 'R':
                opts->R_flag = 1;
                break;
            case 'a':
                opts->a_flag = 1;
                break;
            case 'r':
                opts->r_flag = 1;
                break;
            case 't':
                opts->t_flag = 1;
                break;
            default:
                // Should never reach here since is_valid_option_string() passed
                // But just in case hehe
                illegal_option(arg[j]);
        }
    }
}

void parse(int argc, char **argv, Options *options, char ***paths, int *num_paths) {
    options->l_flag = 0;
    options->R_flag = 0;
    options->r_flag = 0;
    options->a_flag = 0;
    options->t_flag = 0;

    int count = 0;

    // First pass: process options and count operands (paths)
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--") == 0) {
            // Skip the reserved marker
            continue;
        }
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            if (is_valid_option_string(argv[i])) {
                process_option_string(argv[i], options);
                // Do not count as an operand
                continue;
            }
            // Otherwise, argument starts with '-' but is not a valid option string: treat it as an operand
        }
        // Otherwise, treat the argument as an operand
        count++;
    }

    if (count == 0) {
        count = 1;
    }

    // Allocate an array exactly the size needed for the operands
    char **temp_paths = malloc(sizeof(char *) * count);
    if (!temp_paths) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    // Second pass: collect operand arguments.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--") == 0) {
            continue;
        }
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            if (is_valid_option_string(argv[i])) {
                // Already processed as an option; skip adding to operand list
                continue;
            } else {
                // Not a valid option string so treat it as an operand.
                temp_paths[index++] = argv[i];
            }
        } else {
            // Regular argument: treat as an operand.
            temp_paths[index++] = argv[i];
        }
    }
    if (index == 0) {
        static char *default_path = ".";
        temp_paths[index++] = default_path;
    }

    *paths = temp_paths;
    *num_paths = index;
}
