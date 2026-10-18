#include "pscreen_information.h"

void FreeHelpScreen(void)
{
    UnreserveObjPaletteSlot(0);
    ClearHelpScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
}
