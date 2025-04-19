#include "peripherals/uart.h"
#include "io.h"

void uart_putc(int c)
{
    while (io_read(UART0_FR) & FR_TXFF)
        continue;
    io_write(UART0_DR, c);

    if (c == '\n')
        uart_putc('\r');
}

int uart_getc(void)
{
    while (io_read(UART0_FR) & FR_RXFE)
        continue;

    return io_read(UART0_DR);
}

void uart_flush_rx(void)
{
    while (!(io_read(UART0_FR) & FR_RXFE))
        uart_getc();
}

void uart_disable(void)
{
    io_write(UART0_CR,0);
}

void printk(const char *str)
{
    const char *p = str;

    while (*p)
        uart_putc(*p++);
}


void uart_init(void)
{
    io_write(UART0_IMSC, 0);
    io_write(UART0_ICR, 0x7FF);
    io_write(UART0_IBRD, 1);
    io_write(UART0_FBRD, 40);
    io_write(UART0_LCR_H, LCRH_WLEN8);
    io_write(UART0_IFLS, 0);
    io_write(UART0_IMSC, INT_RX);
    io_write(UART0_CR, CR_UART_EN | CR_TXE | CR_RXE);
}
