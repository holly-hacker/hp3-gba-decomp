#include "types.h"
#include "background.h"

void DisableBg(u32 bg)
{
    ClearDispcntFlag(0x100 << bg);
}
