#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct {
    uint64_t x[31];

    uint64_t sp;

    uint64_t pc;

    uint32_t cpsr;

    uint32_t sctlr_el1;

} arm64_cpu_t;

#define FLAG_N (1 << 31)
#define FLAG_Z (1 << 30)
#define FLAG_C (1 << 29)
#define FLAG_V (1 << 28)

typedef uint64_t addr_t;
typedef uint32_t inst_t;

#endif