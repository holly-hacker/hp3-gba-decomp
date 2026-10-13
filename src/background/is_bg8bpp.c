#include "types.h"
#include "background.h"

u32 IsBg8bpp(u32 bg)
{
    return g_BgState.aLayers[bg].control.bits.b8bpp;
}
