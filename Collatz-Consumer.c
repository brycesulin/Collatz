////////////////////////////////////////////////////////////////////////////////
//
// This is an simple program demonstrating shared memory in POSIX systems.
//
// The consumer process reads and outputs the content of the shared memory.
// After compilation, this part should be run after the producer part.
//
// Compile:  gcc  Collatz-Consumer.c  -o  Collatz-Consumer
//
// Run:      ./Collatz-Consumer
//
/////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

int Collatz(int input) {
    if (input % 2 == 0) {
        return input / 2;
    } else {
        return 3 * input + 1;
    }
}

int main() {

    int in;

    /* The size (in bytes) of shared-memory object */
    const int SIZE = 4096;

    /* The name of shared-memory object */
    const char *Obj = "Shm";

    /* The shared-memory file descriptor */
    int shm_fd;

    /* The pointer to shared-memory object */
    void *ptr;

    /* Open the shared-memory object */
    shm_fd = shm_open(Obj, O_RDONLY, 0666);

    if (shm_fd == -1) {
        printf("Shared memory failed\n");
        exit(-1);
    }

    /* Map the shared-memory object in the address space of the process */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    printf("Please input a positive integer: \n");
    scanf("%d", &in);

    if (in <= 0) {
        printf("Not a positive integer!\n");
        exit(3);
    } else if (in > 0) {

        // Declare the variable curr.
        int curr = in;

        printf("Consumer: The output sequence is: ");

        while (curr > 1) {
            printf("%d ", curr);
            curr = Collatz(curr);
        }
        printf("%d \n\n", curr);

        /* Remove the shared-memory object */
        if (shm_unlink(Obj) == -1) {
            printf("Error removing %s\n", Obj);
            exit(-1);
        }

        return 0;
    }
}