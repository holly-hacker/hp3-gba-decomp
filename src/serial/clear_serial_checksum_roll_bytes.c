#include "types.h"
#include "random.h"
#include "serial/serial.h"

void ClearSerialChecksumRollBytes(void)
{
    gMt19937LastRollByte = 0;
    g_bSerialChecksumRollByte = 0;
}
