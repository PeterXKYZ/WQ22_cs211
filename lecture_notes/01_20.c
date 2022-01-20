#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* make_mutatble_string(const char* input) {

    // malloc space for a new string
    char* output = malloc(strlen(input) + 1); // sizeof(char) = 1 so redundant
    if (output == NULL) {
        printf("OUT OF MEMORY MAYBE\n");
        exit(1);
    }

    // copy over memory
    int i = 0;
    for (; input[i] != '\0'; ++i) {
        output[i] = input[i];
    }

    output[i] = '\0';
    // return it

    return output;
}

void to_uppercase(char* input) {
    for (int i=0; input[i] != 0; i++) {
        input[i] = toupper(input[i]);
    }
}

void print_and_destroy(char* input) {
    printf("string is: \"%s\"\n", input);
    free(input);
}


int main(void) {
    char* result = make_mutatble_string("hello");

    to_uppercase(result);
    print_and_destroy(result);
    return 0;
}