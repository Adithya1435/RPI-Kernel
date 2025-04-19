#include "syscalls/syscalls.h"

void syscall_printk(char *str) {
    int syscall_id = 1;
    __asm__ volatile(
        "mov r4, %0\n\t"
        :
        :"r" (syscall_id)
    );

    __asm__ volatile(
        "mov r5, %0\n\t"
        :
        :"r" (str)
    );
    __asm__ volatile(
        "svc #0\n\t"
    );
}



