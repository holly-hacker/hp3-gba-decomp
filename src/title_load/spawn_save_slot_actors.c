#include "types.h"
#include "modes.h"
#include "save.h"
#include "actor.h"
#include "screen_transitions.h"
#include "title_load.h"

// A translucent bar behind each slot, and an opaque copy over the selected one.
void SpawnSaveSlotActors(void)
{
    s32 slot;
    Actor *pActor;

    SetAlphaBlendTargets(0, 2);
    SetAlphaBlendCoefficients(8, 8);

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++)
    {
        pActor = SpawnActor(slot, 0x1C, slot * 28 + 47, g_SaveSlotBarAsset.pPalette);
        SetActorSprite(pActor, &g_SaveSlotBarAsset);
        pActor->oam.priority = 2;
        pActor->oam.objMode = 1;
    }

    g_pSaveSlotCursorActor = SpawnActor(slot, 0x1C, g_GameModeStackContext.dwModeScratchB * 28 + 47,
                                        g_SaveSlotBarAsset.pPalette);
    SetActorSprite(g_pSaveSlotCursorActor, &g_SaveSlotBarAsset);
    g_pSaveSlotCursorActor->oam.priority = 2;
    g_pSaveSlotCursorActor->bDepthSortBias = 0;
}
