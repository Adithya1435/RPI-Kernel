#include "syscalls/syscalls.h"

void umain() {
    //printk("It should not print this and instead triggers exception");
    syscall_printk("Print from user_space using syscall!\n");

}
