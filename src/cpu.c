#include "cpu.h"
#include "memory.h"
#include <stdio.h>

static arm64_cpu_t cpu;

void cpu_init(uint64_t entry_point) {
    mem_init();
    for(int i = 0; i < 31; i++) cpu.x[i] = 0;
    cpu.pc = entry_point;
    cpu.sp = 0x07FFFFFF; 
}

void cpu_step() {
    uint32_t inst = mem_read32(cpu.pc);
    
    if ((inst & 0xFF000000) == 0x91000000) { 
        
    } else if (inst == 0xD503201F) {
    } else if ((inst & 0xFC000000) == 0x14000000) {
        
        uint32_t offset = (inst & 0x03FFFFFF);
        cpu.pc += (offset << 2); 
        return;
    }

    cpu.pc += 4;
}

void cpu_run(int cycles) {
    for(int i = 0; i < cycles; i++) {
        cpu_step();
    }
}

arm64_cpu_t* cpu_get_state() {
    return &cpu;
}