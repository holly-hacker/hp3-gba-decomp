#include "types.h"
#include "serial.h"

s32 InitSerialSession(void)
{
    SetSerialMode(1);
    return BeginSerialSession();
}
