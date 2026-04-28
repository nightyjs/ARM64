#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "types.h"

void cpu_init(uint64_t entry_point);
void cpu_step();
void cpu_run(int cycles);

arm64_cpu_t* cpu_get_state();

#endif