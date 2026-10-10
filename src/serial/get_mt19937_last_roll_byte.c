#include "types.h"
#include "mt19937.h"
#include "serial/serial.h"

s16 GetMt19937LastRollByte(void)
{
    return gMt19937LastRollByte;
}
