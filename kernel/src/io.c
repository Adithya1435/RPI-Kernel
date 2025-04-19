#include "io.h"
#include <stdint.h>

uint32_t io_read(uintptr_t addr) {
    uint32_t val;
    __asm__ volatile ("ldr %0, [%1]"
    : "=r" (val)
    : "r" (addr));
    return val;
}

void io_write(uintptr_t addr, uint32_t val) {
    __asm__ volatile ("str %0, [%1]"
    :
    : "r" (val), "r" (addr));
}

unsigned int curr_mode (void) {
    int mode;
    __asm__ volatile (
        "mrs %0, cpsr\n\t"      // Read CPSR into 'mode'
    "and %0, %0, #0x1F"     // Mask out all bits except the mode bits (lowest 5)
    : "=r" (mode)            // Output: mode will hold the result
    );
    return mode;  // Return the mode
}
