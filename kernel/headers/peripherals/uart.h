#ifndef UART_H
#define UART_H

#include "io.h"

#define UART0_BASE      (PERIPH_BASE + 0x201000)

/* UART Control Reg and Masks */
#define UART0_CR        (UART0_BASE + 0x030)
#define		CR_CTSEN    (1 << 15)
#define		CR_RTSEN    (1 << 14)
#define		CR_OUT2     (1 << 13)
#define		CR_OUT1     (1 << 12)
#define		CR_RTS      (1 << 11)
#define		CR_DTR      (1 << 10)
#define		CR_RXE      (1 << 9)
#define		CR_TXE      (1 << 8)
#define		CR_LBE      (1 << 7)
#define		CR_UART_EN  (1 << 0)


#define UART0_IBRD      (UART0_BASE + 0x024)
#define UART0_FBRD      (UART0_BASE + 0x028)


#define UART0_LCR_H     (UART0_BASE + 0x02c)
#define		LCRH_SPS    (1 << 7)
#define		LCRH_WLEN8  (0x3 << 5)
#define		LCRH_WLEN7  (0x2 << 5)
#define		LCRH_WLEN6  (0x1 << 5)
#define		LCRH_WLEN5  (0x0 << 5)
#define		LCRH_FEN    (1 << 4)
#define		LCRH_STP2   (1 << 3)
#define		LCRH_EPS    (1 << 2)
#define		LCRH_PEN    (1 << 1)
#define		LCRH_BRK    (1 << 0)


#define UART0_DR        (UART0_BASE + 0x000)
#define		DR_OE       (1 << 11)
#define		DR_BE       (1 << 10)
#define		DR_PE       (1 << 9)
#define		DR_FE       (1 << 8)
#define		DR_DATA     (0xff)


#define UART0_FR        (UART0_BASE + 0x018)
#define		FR_TXFE     (1 << 7)
#define		FR_RXFF     (1 << 6)
#define		FR_TXFF     (1 << 5)
#define		FR_RXFE     (1 << 4)
#define		FR_BUSY     (1 << 3)


#define UART0_IFLS      (UART0_BASE + 0x034)
#define UART0_IMSC      (UART0_BASE + 0x038)


#define UART0_ICR       (UART0_BASE + 0x044)
#define		INT_OE		(1 << 10)
#define		INT_BE		(1 << 9)
#define		INT_PE		(1 << 8)
#define		INT_FE		(1 << 7)
#define		INT_RT		(1 << 6)
#define		INT_TX		(1 << 5)
#define		INT_RX		(1 << 4)
#define		INT_DSRM	(1 << 3)
#define		INT_DCDM	(1 << 2)
#define		INT_CTSM	(1 << 1)



void uart_putc(int c);
int uart_getc(void);
void uart_flush_rx(void);
void uart_disable(void);
void printk(const char *str);
int str_length(const char *s);
void str_concat(char *src, char *dest);
int str_to_int(char *s);
void int_to_str(long num, char *buffer);
void uart_init(void);

#endif /* UART_H */
