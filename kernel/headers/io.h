#ifndef IO_H
#define IO_H

#include <stdint.h>

#define PERIPH_BASE     0x3F000000

uint32_t io_read(uintptr_t addr);

void io_write(uintptr_t addr, uint32_t val);

unsigned int curr_mode (void);


#endif /* IO_H */
