#include "types.h"
#include "random.h"
#include "serial/serial.h"

void LatchSerialChecksumRollByte(void)
{
    g_bSerialChecksumRollByte = gMt19937LastRollByte;
}
