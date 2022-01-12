#include "circle.h"

#include <stdio.h>
#include <math.h>

bool valid_circle(struct circle c)
{
    if (c.radius > 0) {
        return true;
    }

    return false;
}

struct circle read_circle(void)
{
    double x = 0;
    double y = 0;
    double radius = -1;

    int num = scanf("%f, %f, %f", &x, &y, &radius);
    printf("num = %d\n", num);
    if (num == 3) {
        return (struct circle) {x, y, radius};
    }
    else {
        return (struct circle) {0, 0, -1};
    } 
}

bool overlapped_circles(struct circle c1, struct circle c2)
{
    //
    // TODO: replace with your code:
    //
    return false;
}

