#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define RAM_SIZE 0x20000000
#define GPU_BASE 0x20000000

void mem_init();
uint8_t* mem_get_ptr();

uint32_t mem_read32(uint64_t addr);
void mem_write32(uint64_t addr, uint32_t value);
uint64_t mem_read64(uint64_t addr);
void mem_write64(uint64_t addr, uint64_t value);

#endif