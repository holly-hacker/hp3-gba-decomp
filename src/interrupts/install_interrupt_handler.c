#include "bios.h"
#include "interrupts.h"
#include "io_regs.h"

void InstallInterruptHandler(void *handlerCode)
{
    // volatile forces this to spill to the stack instead of a register,
    // matching real -- plain u16 keeps it in a register and drops 4 bytes.
    volatile u16 savedIme;

    savedIme = REG_IME;
    REG_IME = 0;
    bios_CPUSet(handlerCode, gIntrHandlerIwram, 0x04000080);
    gIntrVectorPtr = gIntrHandlerIwram;
    bios_CPUSet(gIntrTableTemplate, gIntrTable, 0x0400000D);
    REG_IME = savedIme;
}
