#include <emscripten.h>
#include "memory.h"
#include "cpu.h"
#include "gpu.h"
#include <stdio.h>

EMSCRIPTEN_KEEPALIVE
void vertex_boot() {
    cpu_init(0x0);
    gpu_init();
}

EMSCRIPTEN_KEEPALIVE
uint8_t* get_wasm_memory_ptr() {
    return mem_get_ptr();
}

EMSCRIPTEN_KEEPALIVE
void cpu_run_cycles(int cycles) {
    cpu_run(cycles);
}