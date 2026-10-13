#include "types.h"
#include "background.h"

void ClearBgStateFlags(u32 mask)
{
    g_BgState.dwFlags &= ~mask;
}
