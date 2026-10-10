#include "types.h"
#include "serial/serial.h"

s16 GetSerialChecksumRollByte(void)
{
    return g_bSerialChecksumRollByte;
}
