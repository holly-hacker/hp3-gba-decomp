#include "interrupts.h"
#include "krawall.h"

const IntrFunc gIntrTableTemplate[13] = {
    HandleTimer3Interrupt,
    HandleVBlankInterrupt,
    HandleVCountInterrupt,
    kradInterrupt,  // timer 1
    HandleHBlankInterrupt,
    HandleTimer0Interrupt,
    HandleTimer2Interrupt,
    IntrDummy,  // DMA 0
    IntrDummy,  // DMA 1
    IntrDummy,  // DMA 2
    IntrDummy,  // DMA 3
    IntrDummy,  // keypad
    IntrDummy,  // Game Pak
};
