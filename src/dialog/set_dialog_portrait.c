#include "types.h"
#include "actor.h"
#include "color.h"
#include "sound.h"
#include "dialog.h"
#include "overworld/room_script.h"
#include "hero.h"

// Shows the line's speaker portrait. Blocks 0x7C ("You Receive: \n @1 @2") and 0x7D
// ("You Receive: \n @1 Sickles") use the portrait of the character the player controls.
void SetDialogPortrait(Actor *actor)
{
    if ((u16)(g_DialogState_candidate.wBlockId - 0x7C) <= 1)
    {
        QueueObjPaletteLoadAtOffset(
            (const u8 *)g_aDialogPortraits[g_abPartySlotDialogPortraits[GetPartyMasterStatsSlot_candidate(
                g_pPlayerActor->wCharacterId_candidate)]].pPalette,
            0x20, actor->oam.paletteNum * 16, 0x20);
        SetActorAssetRecord(actor, &g_aDialogPortraits[g_abPartySlotDialogPortraits[GetPartyMasterStatsSlot_candidate(
            g_pPlayerActor->wCharacterId_candidate)]]);
    }
    else
    {
        QueueObjPaletteLoadAtOffset((const u8 *)g_aDialogPortraits[g_dwDialogPortrait].pPalette, 0x20,
                                    actor->oam.paletteNum * 16, 0x20);
        SetActorAssetRecord(actor, &g_aDialogPortraits[g_dwDialogPortrait]);
    }
    actor->dwFlags |= ActorFlagVisible;

    if (g_dwDialogPortrait == 14)
        PlaySoundById(0x32);
    else if (g_dwDialogPortrait == 13)
        PlaySoundById(0x34);
}
