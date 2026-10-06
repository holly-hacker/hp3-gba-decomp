#include "types.h"
#include "game/save.h"

// Writes the Owl Care Kit state: four nibbles (flags, owl name, owl type and
// an unused one), then the stat meters, ticks, care counters and mail timer.
void SerializeOwlCareKit(void)
{
    PackNibblesToSaveStream(&g_saveStateBlock.owlCareKit.bFlags, 4);
    PackBytesToSaveStream(g_saveStateBlock.owlCareKit.abStatMeters, 3);
    PackBytesToSaveStream(g_saveStateBlock.owlCareKit.abCareCounters, 6);
    PackBytesToSaveStream(&g_saveStateBlock.owlCareKit.wElapsedTicks, 2);
    PackBytesToSaveStream(&g_saveStateBlock.owlCareKit.wMailTimer, 2);
}
