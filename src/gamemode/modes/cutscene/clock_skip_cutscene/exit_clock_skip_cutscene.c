#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "hw/mem.h"

void ExitClockSkipCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    UnmuteAllMusicChannels();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
