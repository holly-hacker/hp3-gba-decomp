#include "types.h"
#include "background.h"
#include "combat_fighter.h"
#include "math.h"
#include "save.h"
#include "gen/graphics/overworld.h"
#include "actor.h"
#include "pscreen_folio_bruti.h"
#include "pscreen_folio_bruti_inline.h"
#include "screen_transitions.h"
#include "game_state.h"

// Redraws the detail panel for the monster under the cursor: its sprite, the eight spell names
// with a marker on each effectiveness bar, and its name and description. Monsters that have not
// been analyzed show "?" markers, and unseen ones a silhouette. Only the first 69 monsters have
// data; the grid never reaches past 53.
void DrawFolioBrutiMonsterPanel(void)
{
    u32 monster = g_FolioBrutiState.dwRow * 9 + g_FolioBrutiState.dwColumn;
    u32 tileCursor;
    u32 spell;
    s32 effectiveness;
    s32 x;
    ActorOrbit orbit;
    u32 isUnseen;
    const void *pPalette;

    if (g_FolioBrutiState.pMonster != NULL)
    {
        g_FolioBrutiState.pMonster->dwFlags = (g_FolioBrutiState.pMonster->dwFlags & ~ActorFlagVisible) | 0x82;
        g_FolioBrutiState.pMonster = NULL;
    }

    ClearBgTilemapRect(1, 0xF, 0xA, 0xF, 0xA);
    tileCursor = DrawFolioBrutiSpellLabels(g_FolioBrutiState.dwHeadingTileCursor);

    orbit.wAngleY = 0;
    orbit.wAngleVelX = 0x500;
    orbit.wAngleVelY = 0;
    orbit.wRadiusX = 10;
    orbit.wRadiusY = 0;

    for (spell = 0; spell < 8; spell++)
    {
        if (g_FolioBrutiState.apSpellDots[spell] == NULL)
        {
            g_FolioBrutiState.apSpellDots[spell] = SpawnActor(0, 0, 0, (const ObjPalette *)gActorSprite027Palette);
            SetActorAssetRecord(g_FolioBrutiState.apSpellDots[spell], FOLIO_BRUTI_SPELL_DOT_GFX);
            g_FolioBrutiState.apSpellDots[spell]->oam.priority = 1;
        }

        effectiveness = GetMonsterSpellEffectiveness(monster, spell);
        if (effectiveness == -1 || g_saveStateBlock.abMonsterDocLevel[monster] <= 2)
        {
            SetActorAnimData(g_FolioBrutiState.apSpellDots[spell], FOLIO_BRUTI_SPELL_DOT_GFX,
                              g_aFolioBrutiDotUnknownAnim, 0);
            x = 0xB0 << 13;
            orbit.wAngleX = ((spell << 5) & 0xFF) << 8;
            if (g_FolioBrutiState.dwDotsOrbiting == 0)
                CopyOrbitParamsFromTable(g_FolioBrutiState.apSpellDots[spell], &orbit);
        }
        else
        {
            ClearActorOrbit(g_FolioBrutiState.apSpellDots[spell]);
            SetActorAnimData(g_FolioBrutiState.apSpellDots[spell], FOLIO_BRUTI_SPELL_DOT_GFX,
                              g_aFolioBrutiDotAnims[effectiveness / 0x21], 0);
            x = FixedDivide(effectiveness << 16, 0xC8 << 15) * 0x1A + 0x90000;
        }

        SnapActorPosition(g_FolioBrutiState.apSpellDots[spell], x, (0xB0 + spell * 16) << 15);
    }

    if (g_saveStateBlock.abMonsterDocLevel[monster] <= 2)
        g_FolioBrutiState.dwDotsOrbiting = 1;
    else
        g_FolioBrutiState.dwDotsOrbiting = 0;

    if (monster <= 0x44)
    {
        if (g_saveStateBlock.abMonsterDocLevel[monster] != 0)
        {
            SetAlphaBlendCoefficients(6, 10);
            pPalette = g_pMonsterGraphicsTable[monster].battle.pPalette;
            isUnseen = 0;
        }
        else
        {
            SetAlphaBlendCoefficients(6, 10);
            pPalette = g_aFolioBrutiBlankObjPalette;
            isUnseen = 1;
        }

        g_FolioBrutiState.pMonster = SpawnActor(0, 0xB8, 0x4C, (const ObjPalette *)pPalette);
        SetActorAnimData(g_FolioBrutiState.pMonster, &g_pMonsterGraphicsTable[monster],
                          g_pMonsterAnimFrameTable[monster], 0);
        g_FolioBrutiState.pMonster->oam.priority = 1;
        if (isUnseen)
            g_FolioBrutiState.pMonster->oam.objMode = 1;
        SetActorAffineTransform(g_FolioBrutiState.pMonster, g_adwFolioBrutiMonsterScale[monster],
                                 g_adwFolioBrutiMonsterScale[monster], 0, 3);

        DrawFolioBrutiMonsterText();
    }
}
