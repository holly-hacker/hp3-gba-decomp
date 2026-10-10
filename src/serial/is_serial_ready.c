#include "types.h"
#include "serial/serial.h"

u32 IsSerialReady(void)
{
    return IsSerialUp();
}
