///////////////////////////////////////////////////////////////////////////////////
//
// This is an simple program demonstrating shared memory in POSIX systems.
//
// The producer process writes to the shared memory region. After compilation,
// this part should be run first.
//
// Compile:  gcc  Collatz-Producer.c  -o  Collatz-Producer
//
// Run:      ./Collatz-Producer
//
///////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <zconf.h>

int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 2) {
        printf("Please enter 2 arguments!\n");
        exit(1);
    } else if (argc == 2) {

        int arg1 = atoi(argv[1]);

        /* The size (in bytes) of shared-memory object */
        const int SIZE = 4096;

        /* The name of shared-memory object */
        const char *Obj = "Shm";

        /* The shared-memory file descriptor */
        int shm_fd;

        /* The pointer to shared-memory object */
        void *ptr;

        /* Create the shared-memory object */
        shm_fd = shm_open(Obj, O_CREAT | O_RDWR, 0666);

        /* Configure the size of the shared-memory object */
        ftruncate(shm_fd, SIZE);

        /* Map the shared-memory object in the address space of the process */
        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

        if (ptr == MAP_FAILED) {
            printf("Map failed\n");
            return -1;
        }

        /* Create a message and write it to the shared-memory object */
        if (arg1 <= 0) {
            printf("Not a positive integer!\n");
            exit(3);
        } else if (arg1 > 0) {
            fgets(ptr, SIZE, __stdoutp);
            printf("Producer: Writing the sequence to the shared-memory object is done! \n");

            return 0;
        }
    }
}
