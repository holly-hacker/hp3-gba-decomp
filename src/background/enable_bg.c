#include "types.h"
#include "background.h"

void EnableBg(u32 bg)
{
    SetDispcntFlag(0x100 << bg);
}
