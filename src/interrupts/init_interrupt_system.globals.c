#include "types.h"
#include "hw/interrupts.h"
#include "hw/vblank.h"

const u32 gIntrTableTemplate[13] = {
    (u32)HandleTimer3Interrupt_candidate,
    (u32)HandleVBlankInterrupt,
    (u32)HandleVCountInterrupt,
    (u32)IwramTimer1Handler,
    (u32)HandleHBlankInterrupt_candidate,
    (u32)HandleTimer0Interrupt_candidate,
    (u32)HandleTimer2Interrupt,
    (u32)IntrDummy,  // DMA 0
    (u32)IntrDummy,  // DMA 1
    (u32)IntrDummy,  // DMA 2
    (u32)IntrDummy,  // DMA 3
    (u32)IntrDummy,  // keypad
    (u32)IntrDummy,  // Game Pak
};
