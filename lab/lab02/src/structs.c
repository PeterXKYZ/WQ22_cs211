#include <stdio.h>

/*
 * Struct definitions
 */

struct apple
{
    double weight;
    const char* variety;
    const char* color;
};

struct animal
{
    int age;
    const char* species;
    const char* gender;
};

// Function definitiona
void print_animal(struct animal);

/*
 * Function definitions
 */

int main(void)
{
    struct apple delicious = { 0.3, "Red Delicious", "red" };

    printf("My %s apple is the color %s and weighs %g lbs.\n",
           delicious.variety, delicious.color, delicious.weight);

    struct animal doggy = { 100, "Canis familiaris", "male" };
    printf("This is a %s %s aged %d years old.\n",
            doggy.gender, doggy.species, doggy.age);

    print_animal(doggy);

    return 0;
}

void print_animal(struct animal an_animal)
{
    printf("Age: %d\nSpecies: %s\nGender: %s\n",
        an_animal.age, an_animal.species, an_animal.gender);

    if (an_animal.age >= 10) {
        printf("This animal is old!\n");
    }
    else {
        printf("This animal is not that old\n");
    }
}
