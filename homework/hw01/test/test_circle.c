// test_circle - Tests for the functions in ../src/circle.c.

#include "../src/circle.h"
#include <211.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

// "Factory function" for easily constructing circles.
struct circle make_circle(double x, double y, double radius)
{
    return (struct circle) {x, y, radius};
}

// Tests that tangent circles are not considered overlapped.
void test_tangent(void)
{
    // Hint: “!” means “not”, so this is an assertion that the
    // two circles *don’t* overlap.
    CHECK(! overlapped_circles(make_circle(0, 0, 2), make_circle(4, 0, 2)));
}

// Tests that more distance circles are not considered overlapped.
void test_not_overlapped(void)
{
    CHECK(! overlapped_circles(make_circle(0, 0, 2), make_circle(5, 0, 2)));
    CHECK(! overlapped_circles(make_circle(0, 0, 2), make_circle(6, 0, 2)));
}

// Tests that two overlapping circles returns true
void test_overlapped(void)
{
    CHECK(overlapped_circles(make_circle(1.02, .32, 1), make_circle(-.17, 1.15, 1.8)));
}

// Tests that two same circles returns true
void test_same(void)
{
    CHECK(overlapped_circles(make_circle(1, 3, 2), make_circle(1, 3, 2)));
}

int main(void)
{
    test_tangent();
    test_not_overlapped();
    test_overlapped();
    test_same();
}
