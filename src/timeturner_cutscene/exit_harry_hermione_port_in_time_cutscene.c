#include "actor.h"
#include "move.h"
#include "screen_transitions.h"
#include "scroll.h"
#include "timeturner_cutscene.h"

void ExitHarryHermionePortInTimeCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeRoomCollision();
    FreeBgTileBitOffsets();
}
