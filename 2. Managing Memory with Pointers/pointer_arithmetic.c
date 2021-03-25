#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int count = 4;
    int *my_ptr = (int*)malloc(count * sizeof(int));

    // 1. Simple pointer addition - notice how addresses printed in the console are not increased by 1 but by the total size of the "int" type
    for(int i = 0; i < count; i++) {
        printf("'my_ptr' address: %p\n", my_ptr + i);
    }

    int initial_value = 5;
    for(int i = 0; i < count; i++) {
        // 2. Assigning values to the memory addresses using pointer arithmetic
        *(my_ptr + i) = initial_value++;

        // 3. Dereferencing pointers using pointer arithmetic
        printf("'my_ptr' position %d value: %d\n", i, *(my_ptr + i));
    }

    // 4. Can be easy to accidentally lose address offsets
    int *my_other_ptr = (int*)malloc(count * sizeof(int));
    printf("\nStarting address of malloc'd block: %p\n", my_other_ptr);

    for(int i = 0; i < count; i++) {
        // Here we are accidentally incrementing the pointer variable itself - Note the difference between
        printf("'my_other_ptr' address: %p\n", my_other_ptr++);
    }

    printf("Still expecting this to be the starting address of malloc'd block: %p\n", my_other_ptr);
    // ^^ We have now lost the starting position of this malloc'd block of memory
    return 0;
}
