// overlapped - Reads a target circle, then any number of candidate
// circles. Prints "overlapped\n" for each candidate circle that
// intersects the target and "not overlapped\n" for each candidate
// circle that does not. Exits after reading an invalid circle.

#include "circle.h"
#include <stdio.h>

#define OVERLAPPED_MSG      "overlapped\n"
#define NOT_OVERLAPPED_MSG  "not overlapped\n"

int main(void)
{
    struct circle target = read_circle();

    if (valid_circle(target) == false) {
        return 1;
    }

    while (true) {
        struct circle candidate = read_circle();
        if (valid_circle(candidate) == false) {
            break;
        }

        bool ovla = overlapped_circles(target, candidate);
        if (ovla == true) {
            printf(OVERLAPPED_MSG);
        }
        else {
            printf(NOT_OVERLAPPED_MSG);
        }
    }
    
    return 0;
}
