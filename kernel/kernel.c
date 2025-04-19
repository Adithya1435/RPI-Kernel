#include "peripherals/uart.h"

void switch_to_user_mode (void){
    __asm__ volatile (
    "mrs r0, cpsr\n\t"
    "bic r0, r0, #0x1F\n\t"
    "orr r0, r0, #0x10\n\t"
    "msr cpsr_c, r0\n\t"
    "blx umain\n\t"
    );
}


void kmain (void) {

    uart_init();
    uart_flush_rx();

    printk("Hello from kernel space!!\n");

    switch_to_user_mode();

    while(1) {}

}
