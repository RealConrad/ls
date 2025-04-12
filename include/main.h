#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int l_flag;
    int R_flag;
    int r_flag;
    int a_flag;
    int t_flag;
}   Options;

/* --------------------------------- PARSER --------------------------------- */
void parse(int argc, char **argv, Options *options, char ***paths, int *num_paths);

#endif