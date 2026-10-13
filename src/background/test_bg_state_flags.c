#include "types.h"
#include "background.h"

u32 TestBgStateFlags(u32 mask)
{
    return g_BgState.dwFlags & mask;
}
