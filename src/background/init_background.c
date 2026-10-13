#include "types.h"
#include "background.h"

void InitBackground(void)
{
    s32 i;

    ResetDisplayState(0);
    g_BgState.dwFlags = 0;
    // Empty countdown over the four layers; original body likely empty
    for (i = 3; i >= 0; i--)
        ;
}
