#include "types.h"
#include "video.h"

u32 GetScanlineEffectLine(u32 index)
{
    return g_ScanlineEffectState.aEntries[index].wLine;
}
