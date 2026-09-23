#include "types.h"
#include "audio.h"
#include "display.h"
#include "mem.h"

void ExitClockSkipCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    UnmuteAllMusicChannels();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
