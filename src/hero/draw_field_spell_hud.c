#include "actor.h"
#include "color.h"
#include "font.h"
#include "hero.h"
#include "text.h"
#include "text_actor.h"

void DrawFieldSpellHud(u32 fieldSpell)
{
    s32 textId;
    u8 fighterType;
    const u8 *pText;

    textId = g_aFieldSpells[g_bSelectedFieldSpell].dwSpell + 0x51B;  // "Flipendo"
    fighterType = g_aFieldSpells[fieldSpell].bFighterType;
    SelectTextFont(9, 0, 0);
    if (g_pFieldSpellNameActor != NULL)
    {
        pText = GetDialogText(textId);
        SetTextActorString(g_pFieldSpellNameActor, pText);
        g_pFieldSpellNameActor->dwStateTimer = 0;
        g_pFieldSpellNameActor->dwFlags |= ActorFlagVisible;
    }
    else
    {
        pText = GetDialogText(textId);
        g_pFieldSpellNameActor = SpawnTextActor(&pText, 0);
        g_pFieldSpellNameActor->dwFlags |= ActorFlagHasSpriteCells;
        g_pFieldSpellNameActor->oam.priority = 0;
        g_pFieldSpellNameActor->oam.paletteNum = 2;
        g_pFieldSpellNameActor->dwStateTimer = 0;
        SetActorPosition(g_pFieldSpellNameActor, 6, 24);
    }

    if (g_pFieldSpellPortraitActor != NULL)
        FreeActor(g_pFieldSpellPortraitActor);
    g_pFieldSpellPortraitActor = SpawnActor(0, 26, 22, NULL);
    QueueObjPaletteLoad(g_aFieldSpellPortraitAssets[fighterType].pPalette->aColors, 0x10, 16);
    SetActorAssetRecord(g_pFieldSpellPortraitActor, &g_aFieldSpellPortraitAssets[fighterType]);
    g_pFieldSpellPortraitActor->dwFlags |= ActorFlagHasSpriteCells;
    g_pFieldSpellPortraitActor->oam.priority = 0;
    g_pFieldSpellPortraitActor->oam.paletteNum = 1;
}
