#include "random.h"
#include "serial.h"

void LatchSerialChecksumRollByte(void)
{
    g_bSerialChecksumRollByte = gMt19937LastRollByte;
}
