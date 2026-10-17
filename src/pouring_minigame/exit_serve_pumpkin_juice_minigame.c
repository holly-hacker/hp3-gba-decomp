#include "char_block.h"
#include "color.h"
#include "actor.h"
#include "sound.h"
#include "pouring_minigame.h"
#include "screen_transitions.h"

void ExitUnusedServePumpkinJuiceMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ResetPaletteAnimations();
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0803FF04();
    FreeBgTileAnimations();
}
