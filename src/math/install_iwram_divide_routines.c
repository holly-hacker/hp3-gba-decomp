#include "divide.h"
#include "hw/bios.h"

// Copies DivideSignedQuotient, DivideSignedRemainder and
// DivideUnsignedWorker (contiguous ARM code) to IWRAM and records each
// copy's entry point for the iwramDivide* veneers.
void InstallIwramDivideRoutines(void)
{
    bios_CPUSet(DivideSignedQuotient, g_abIwramDivideCode, 0x04000000 | (sizeof(g_abIwramDivideCode) / 4));
    g_pfnIwramDivideSignedQuotient = (void *)g_abIwramDivideCode;
    g_pfnIwramDivideSignedRemainder = (void *)(g_abIwramDivideCode + 0x28);
    g_pfnIwramDivideUnsigned = (void *)(g_abIwramDivideCode + 0x64);
}
