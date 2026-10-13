#include "types.h"
#include "background.h"

void ClearBgStateFlag0(void)
{
    g_BgState.dwFlags &= ~1;
}
