#include "translate.h"

#include <211.h>

#include <stdio.h>
#include <string.h>


#define USAGE_MESSAGE   "Usage: %s FROM TO < INPUT_FILE\n"
#define LENGTH_MESSAGE  "%s: error: lengths of FROM and TO differ\n"
#define OOM_MESSAGE     "%s: error: out of memory\n"


int main(int argc, char* argv[])
{
    if (argc != 3) {    // mismatched arguments
        fprintf(stderr, USAGE_MESSAGE, argv[0]);
        return 1;
    }

    char* from = expand_charseq(argv[1]);
    char* to   = expand_charseq(argv[2]);

    if (from == NULL || to == NULL) {   // if either pointer is NULL, error
        fprintf(stderr, OOM_MESSAGE, argv[0]);
        return 10;
    }

    if (strlen(from) != strlen(to)) {   // if from and to have different lengths, error
        fprintf(stderr, LENGTH_MESSAGE, argv[0]);
        free(from);     // don't forget to free from and to in this branch
        free(to);
        return 2;
    }

    char* line;

    while ((line = read_line()) != NULL) {
        translate(line, from, to);
        printf("%s\n", line);
        free(line);
    }

    free(to);
    free(from);

    return 0;
}
