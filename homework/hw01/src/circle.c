#include "circle.h"

#include <stdio.h>
#include <math.h>

bool valid_circle(struct circle c)
{
    if (c.radius > 0) {
        return true;
    }
    else {
        return false;
    }
}

struct circle read_circle(void)
{
    double x = 0;
    double y = 0;
    double radius = -1;

    int num = scanf("%lf %lf %lf", &x, &y, &radius);
    // lf = long float, specifier for double
    // printf("num = %d\n", num);
    if (num == 3) {
        return (struct circle) {x, y, radius};
    }
    else {
        return (struct circle) {0, 0, -1};
    } 
}

bool overlapped_circles(struct circle c1, struct circle c2)
{
    double sum_of_radii = c1.radius + c2.radius;
    double sum_of_radii_squared = sum_of_radii * sum_of_radii;

    double x_difference = c1.x - c2.x;
    double y_difference = c1.y - c2.y;
    double center_distance_squared = 
        x_difference * x_difference + y_difference * y_difference;

    if (sum_of_radii_squared > center_distance_squared) {
        return true;
    }
    else {
        return false;
    }
}

