#include "actor.h"
#include "color.h"
#include "font.h"
#include "hero.h"
#include "map.h"
#include "text.h"
#include "text_actor.h"
#include "overworld/room.h"

void ShowMapNamePopup(void)
{
    s32 textId = g_bCurrentRoomId + 0x54A;  // "Defense Against the Dark Arts Classroom"
    u32 shownTicks = 0;  // TickMapNameActor slides the popup away after 40 ticks
    const u8 *pText;

    // The popup draws with palette bank 2, shared with the field spell icon.
    QueueObjPaletteLoad(
        g_aFieldSpellIconAssets[g_aFieldSpells[g_bSelectedFieldSpell].dwSpell].pPalette->aColors,
        0x20, 16);
    SelectTextFont(9, 0, 0);
    if (g_pMapNameTextActor != NULL)
    {
        pText = GetDialogText(textId);
        SetTextActorString(g_pMapNameTextActor, pText);
        g_pMapNameTextActor->dwFlags |= ActorFlagVisible;
        g_pMapNameTextActor->dwStateTimer = shownTicks;
        g_pMapNamePopupActor->dwFlags |= ActorFlagVisible;
        g_pMapNamePopupActor->dwStateTimer = shownTicks;
    }
    else
    {
        g_pMapNamePopupActor = SpawnActor(0, 0, 151, NULL);
        SetActorAssetRecord(g_pMapNamePopupActor, &g_MapNamePopupAsset);
        g_pMapNamePopupActor->dwFlags |= ActorFlagHasSpriteCells;
        g_pMapNamePopupActor->oam.priority = 0;
        g_pMapNamePopupActor->oam.paletteNum = 2;
        g_pMapNamePopupActor->pfnTick = TickMapNameActor;
        g_pMapNamePopupActor->dwStateTimer = shownTicks;

        pText = GetDialogText(textId);
        g_pMapNameTextActor = SpawnUnslottedTextActor(&pText);
        g_pMapNameTextActor->dwFlags |= ActorFlagHasSpriteCells;
        g_pMapNameTextActor->oam.priority = 0;
        g_pMapNameTextActor->oam.paletteNum = 2;
        g_pMapNameTextActor->pfnTick = TickMapNameActor;
        g_pMapNameTextActor->dwStateTimer = shownTicks;
        SetTextActorCenterPosition_candidate(g_pMapNameTextActor, 120, 152);
    }
}
