#include "main.h"
#include "stdio.h"

static void debug_print_all(Options options, char **paths) {
    printf("OPTIONS:\nl: %d\nR: %d\nr: %d\na: %d\nt: %d\n",
        options.l_flag, options.R_flag, options.r_flag, options.a_flag, options.t_flag);
    printf("\n");
    int i = 0;
    while (paths[i]) {
        printf("Path[%d]: %s\n", i, paths[i]);
        i++;
    }
}

int main(int argc, char **argv) {
    Options options;
    char **paths;
    int num_paths;

    parse(argc, argv, &options, &paths, &num_paths);

    debug_print_all(options, paths);

    free(paths);
}
