#ifndef MM_H
#define MM_H

#define PAGE_SIZE 4096
#define KERNEL_START 0x8000
#define USER_START   0x400000

#define MMU_SECTION (2 << 0)
#define MMU_CACHEABLE (1 << 3)
#define MMU_BUFFERABLE (1 << 2)
#define MMU_PERMISSION (1 << 10)

void mmu_init(void);

#endif
