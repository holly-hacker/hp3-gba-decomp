#pragma once

#include "types.h"

typedef struct {
    const void *src;
    void *dst;
    u32 cnt;
} DmaRegs;

#define REG_DMA3 (*(volatile DmaRegs *)0x040000D4)
