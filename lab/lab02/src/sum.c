#include <stdio.h>

/*
 * Function declarations
 */

int sum_numbers(int);


/*
 * Function definitions
 */

int main(void)
{
    int initial_number = 42;
    int result = sum_numbers(initial_number);

    printf("sum_numbers(%d) returns %d\n", initial_number, result);

    return 0;
}

int sum_numbers(int num)
{
    int sum = 0;
    for (int i = 1; i <= num; ++i) {
        sum += i;
    }
    return sum;
}

