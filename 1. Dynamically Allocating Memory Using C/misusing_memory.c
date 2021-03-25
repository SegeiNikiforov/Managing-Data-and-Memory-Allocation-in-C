#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    int age;
    char* name;
} Person;

int main(int argc, char* argv[]) {
    // 1. Dangling pointers
    Person *person = (Person*)malloc(sizeof(Person));
    person = NULL;

    // 2. Double frees
    Person *person2 = (Person*)malloc(sizeof(Person));
    free(person2);
//    free(person2);

    // 3. Forgetting to use "sizeof"
    int *int_ptr = (int*)malloc(2);
    free(int_ptr);

    // 4. NULL pointer returned from malloc, calloc, realloc
    char *name = (char*)malloc(100000000);
    *name = 'A'; // We could be dereferencing an invalid pointer here

    return 0;
}
