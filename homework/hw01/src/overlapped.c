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
    struct circle c = read_circle();
    bool valid = valid_circle(c);
    printf("%d", valid);
}
