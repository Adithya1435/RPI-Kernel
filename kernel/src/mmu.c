#include "mmu.h"

unsigned int page_table[4096] __attribute__((aligned(16384)));

void mmu_init(void) {
    // Identity map - Kernel for 64MB (1MB region)
    for (unsigned int i = 0; i < 64; i++) {
        page_table[i] = (i * 0x100000) | MMU_SECTION | MMU_PERMISSION;
    }

    // Identity map - User
    for (unsigned int i = 0x400000 / 0x100000; i < (0x400000 / 0x100000) + 16; i++) {
        page_table[i] = (i * 0x100000) | MMU_SECTION | MMU_PERMISSION;
    }

    // Map UART
    page_table[0x3F200000 >> 20] = 0x3F200000 | MMU_SECTION | MMU_PERMISSION;

    // TTBR0
    __asm__ volatile("mcr p15, 0, %0, c2, c0, 0" :: "r"(page_table));

    // DACR - Full control
    __asm__ volatile("mcr p15, 0, %0, c3, c0, 0" :: "r"(0x55555555));

    // SCTLR
    unsigned int control;
    __asm__ volatile("mrc p15, 0, %0, c1, c0, 0" : "=r"(control));
    control |= (1 << 0);    // Enable MMU
    control &= ~(1 << 29);
    __asm__ volatile("mcr p15, 0, %0, c1, c0, 0" :: "r"(control));
    __asm__ volatile("isb");
}
