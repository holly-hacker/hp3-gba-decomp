#include "types.h"
#include "random.h"
#include "serial/serial.h"

s16 GetMt19937LastRollByte(void)
{
    return gMt19937LastRollByte;
}
