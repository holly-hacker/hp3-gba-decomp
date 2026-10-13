#include "types.h"
#include "background.h"

void SetBgStateFlags(u32 mask)
{
    g_BgState.dwFlags |= mask;
}
