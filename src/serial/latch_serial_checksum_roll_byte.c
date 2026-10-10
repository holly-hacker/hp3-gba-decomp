#include "types.h"
#include "mt19937.h"
#include "serial/serial.h"

void LatchSerialChecksumRollByte(void)
{
    g_bSerialChecksumRollByte = gMt19937LastRollByte;
}
