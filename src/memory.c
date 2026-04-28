#include "memory.h"
#include "gpu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint8_t* ram_ptr = NULL;

void mem_init() {
    ram_ptr = (uint8_t*)aligned_alloc(4096, RAM_SIZE);
    if (!ram_ptr) {
        return;
    }
    memset(ram_ptr, 0, RAM_SIZE);
}

uint8_t* mem_get_ptr() {
    return ram_ptr;
}

void mem_write32(uint64_t addr, uint32_t value) {
    
    if (addr >= GPU_BASE && addr < (GPU_BASE + 0x1000)) {
        gpu_mmio_write(addr - GPU_BASE, value);
        return;
    }

    if (addr < RAM_SIZE) {
        *(uint32_t*)(&ram_ptr[addr]) = value;
    }
}

uint32_t mem_read32(uint64_t addr) {
    if (addr < RAM_SIZE) {
        return *(uint32_t*)(&ram_ptr[addr]);
    }
    return 0;
}

void mem_write64(uint64_t addr, uint64_t value) {
    if (addr < RAM_SIZE) *(uint64_t*)(&ram_ptr[addr]) = value;
}

uint64_t mem_read64(uint64_t addr) {
    if (addr < RAM_SIZE) return *(uint64_t*)(&ram_ptr[addr]);
    return 0;
}