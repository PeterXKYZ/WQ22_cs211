#include <stdio.h>

#include "lab3_funs.h"

int main(void) {
    // How to use str_chr:
    printf("'o' is found in \"hello NUsolar club!\" at \"%s\"\n",
           str_chr("hello NUsolar club!",'o'));

    // How to use is_prefix_of:
    printf("is_prefix_of(HELLO, HE) returns %s\n",
            is_prefix_of("HELLO", "HE") ? "true" : "false");
    printf("is_prefix_of(BYEBYE, BEE) returns %s\n",
            is_prefix_of("BYEBYE", "BEE") ? "true" : "false");

    // How you might use str_str:
    printf("str_str says that ME is here: %s\n",
            str_str("WELCOME INTO 211", "ME"));

    return 0;
}

