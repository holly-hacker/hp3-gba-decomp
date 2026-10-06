#include "types.h"
#include "game/save.h"

// Reads the Owl Care Kit state: four nibbles (flags, owl name, owl type and
// an unused one), then the stat meters, ticks, care counters and mail timer.
void DeserializeOwlCareKit(void)
{
    UnpackNibblesFromSaveStream(&g_saveStateBlock.owlCareKit.bFlags, 4);
    UnpackBytesFromSaveStream(g_saveStateBlock.owlCareKit.abStatMeters, 3);
    UnpackBytesFromSaveStream(g_saveStateBlock.owlCareKit.abCareCounters, 6);
    UnpackBytesFromSaveStream(&g_saveStateBlock.owlCareKit.wElapsedTicks, 2);
    UnpackBytesFromSaveStream(&g_saveStateBlock.owlCareKit.wMailTimer, 2);
}
