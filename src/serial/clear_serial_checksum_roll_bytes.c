#include "types.h"
#include "mt19937.h"
#include "serial/serial.h"

void ClearSerialChecksumRollBytes(void)
{
    gMt19937LastRollByte = 0;
    g_bSerialChecksumRollByte = 0;
}
