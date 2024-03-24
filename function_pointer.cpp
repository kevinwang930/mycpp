#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

// The machine code for a simple function that returns the value 42.
// This is the binary representation of the following assembly instructions:
//    mov eax, 42
//    ret
const unsigned char machineCode[] = {
        0xB8, 0x2A, 0x00, 0x00, 0x00, // mov eax, 42
        0xC3                          // ret
};

int main() {
    // Calculate the size of a memory page on the system
    size_t pageSize = getpagesize();

    // Allocate one page of memory with execute permissions
    void *codeBuffer = mmap(NULL, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (codeBuffer == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Copy the machine code to the allocated memory
    memcpy(codeBuffer, machineCode, sizeof(machineCode));

    // Define a function pointer type matching the calling convention of the machine code
    typedef int (*FunctionPtr)();

    // Cast the memory buffer to the function pointer type
    FunctionPtr func = (FunctionPtr)codeBuffer;

    // Call the function (execute the machine code)
    int result = func();
    printf("The function returned: %d\n", result);

    // Deallocate the memory
    if (munmap(codeBuffer, pageSize) == -1) {
        perror("munmap");
        return 1;
    }

    return 0;
}