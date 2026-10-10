#include "types.h"
#include "battle/battle.h"
#include "battle/effect_script.h"
#include "math.h"
#include "game/save.h"
#include "gen/graphics/overworld.h"
#include "graphics/display.h"
#include "graphics/object.h"
#include "graphics/text.h"
#include "menu/folio_bruti.h"
#include "menu/folio_bruti_inline.h"

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
    u16 aOrbit[6];
    u32 isUnseen;
    const void *pPalette;

    if (g_FolioBrutiState.pMonster != NULL)
    {
        g_FolioBrutiState.pMonster->dwFlags = (g_FolioBrutiState.pMonster->dwFlags & ~ObjectFlagVisible) | 0x82;
        g_FolioBrutiState.pMonster = NULL;
    }

    sub_080075A8(1, 0xF, 0xA, 0xF, 0xA);
    tileCursor = DrawFolioBrutiSpellLabels(g_FolioBrutiState.dwHeadingTileCursor);

    aOrbit[1] = 0;
    aOrbit[2] = 0x500;
    aOrbit[3] = 0;
    aOrbit[4] = 10;
    aOrbit[5] = 0;

    for (spell = 0; spell < 8; spell++)
    {
        if (g_FolioBrutiState.apSpellDots[spell] == NULL)
        {
            g_FolioBrutiState.apSpellDots[spell] = SpawnObject(0, 0, 0, (const ObjPalette *)gObjectSprite027Palette);
            SetObjectAssetRecord(g_FolioBrutiState.apSpellDots[spell], FOLIO_BRUTI_SPELL_DOT_GFX);
            g_FolioBrutiState.apSpellDots[spell]->oam.priority = 1;
        }

        effectiveness = GetMonsterSpellEffectiveness(monster, spell);
        if (effectiveness == -1 || g_saveStateBlock.abMonsterDocLevel[monster] <= 2)
        {
            SetObjectAnimData(g_FolioBrutiState.apSpellDots[spell], FOLIO_BRUTI_SPELL_DOT_GFX,
                              g_aFolioBrutiDotUnknownAnim, 0);
            x = 0xB0 << 13;
            aOrbit[0] = ((spell << 5) & 0xFF) << 8;
            if (g_FolioBrutiState.dwUnk0 == 0)
                CopyOrbitParamsFromTable(g_FolioBrutiState.apSpellDots[spell], aOrbit);
        }
        else
        {
            sub_080039E8(g_FolioBrutiState.apSpellDots[spell]);
            SetObjectAnimData(g_FolioBrutiState.apSpellDots[spell], FOLIO_BRUTI_SPELL_DOT_GFX,
                              g_aFolioBrutiDotAnims[effectiveness / 0x21], 0);
            x = FixedDivide(effectiveness << 16, 0xC8 << 15) * 0x1A + 0x90000;
        }

        SnapObjectPosition(g_FolioBrutiState.apSpellDots[spell], x, (0xB0 + spell * 16) << 15);
    }

    if (g_saveStateBlock.abMonsterDocLevel[monster] <= 2)
        g_FolioBrutiState.dwUnk0 = 1;
    else
        g_FolioBrutiState.dwUnk0 = 0;

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

        g_FolioBrutiState.pMonster = SpawnObject(0, 0xB8, 0x4C, (const ObjPalette *)pPalette);
        SetObjectAnimData(g_FolioBrutiState.pMonster, &g_pMonsterGraphicsTable[monster],
                          g_pMonsterAnimFrameTable[monster], 0);
        g_FolioBrutiState.pMonster->oam.priority = 1;
        if (isUnseen)
            g_FolioBrutiState.pMonster->oam.objMode = 1;
        SetObjectAffineTransform(g_FolioBrutiState.pMonster, g_adwFolioBrutiMonsterScale[monster],
                                 g_adwFolioBrutiMonsterScale[monster], 0, 3);

        DrawFolioBrutiMonsterText();
    }
}
