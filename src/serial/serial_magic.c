#include "types.h"
#include "serial.h"

// Marker words; no reader is known.
const u32 g_adwSerialMagic[4] = {
    0xB0CAFEED,
    0x0FFFA000,
    0xC0DEBEEF,
    0xDEADBABE,
};
