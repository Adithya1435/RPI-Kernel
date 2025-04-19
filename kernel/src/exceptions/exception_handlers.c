#include "peripherals/uart.h"
#include "exceptions/exception_handlers.h"


void handle_svc(unsigned int *regs) {

    unsigned int syscall_id = regs[4];
    char *str = (char *)regs[5];

    switch (syscall_id) {
        case 1:
            printk(str);
            break;
        default:
            printk("Unknown syscall\n");
    }
}

void handle_data_abort(unsigned int *regs){
    printk("Data Abort Exception!");
}

void handle_prefetch_abort(unsigned int *regs){
    printk("Prefetch Abort Exception!");
}
