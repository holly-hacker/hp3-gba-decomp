#include "types.h"
#include "background.h"
#include "color.h"
#include "combat_2.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/rewards.h"
#include "battle/battle.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "combat_result.h"
#include "gen/graphics/menus.h"

// Copies the portrait of the party member in stats slot g_abCombatResultPartySlots[partyPos]
// from the loaded BG graphic to the screen position of portrait index pos.
#define COPY_PORTRAIT(bg, pTilemap, rects, positions, partyPos, pos)                              \
    CopyBgTilemapRect(bg, pTilemap, 1, 0, rects[g_abCombatResultPartySlots[partyPos]].bSrcX,                \
                 rects[g_abCombatResultPartySlots[partyPos]].bSrcY, positions[pos].bDstX,              \
                 positions[pos].bDstY, rects[g_abCombatResultPartySlots[partyPos]].bWidth,             \
                 rects[g_abCombatResultPartySlots[partyPos]].bHeight)

void InitializeCombatResult(void)
{
    volatile u16 zero;
    u32 xp;
    u32 flags;

    g_wCombatResultXpNumberX = 0;
    g_pCombatResultCoinActor = 0;
    g_pCombatResultItem0Actor = 0;
    g_pCombatResultItem1Actor = 0;

    g_dwCombatResultXpRemaining = xp = g_nBattleXpReward;
    flags = g_dwBattleRewardFlagsSnapshot;
    if (flags & ExtraExpBonus)
        g_dwCombatResultXpRemaining = xp * 3;

    if (flags & GrantExtraXp)
        g_dwCombatResultXpRemaining = g_dwCombatResultXpRemaining * 3 / 2;

    if (GetPartySize() == 3)
    {
        g_abCombatResultPartySlots[0] = 1;
        g_abCombatResultPartySlots[1] = 2;
        g_abCombatResultPartySlots[2] = 0;
    }
    else if (GetPartySize() == 2)
    {
        g_abCombatResultPartySlots[0] = GetPartyMasterStatsSlot_candidate(g_bPartyCharId0);
        g_abCombatResultPartySlots[1] = GetPartyMasterStatsSlot_candidate(g_bPartyCharId1);
    }
    else if (GetPartySize() == 1)
    {
        g_abCombatResultPartySlots[2] = GetPartyMasterStatsSlot_candidate(g_bPartyCharId0);
    }

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(3, g_dwCombatResultBg3Control);
    ClearBgTilemap(3);
    LoadBgGraphic(3, gEquipCharacterSelect001, 1, 0, 0, 0);
    SetBgControl(1, g_dwCombatResultBg1Control);
    ClearBgTilemap(1);
    SetBgControl(2, g_dwCombatResultBg2Control);
    ClearBgTilemap(2);

    if (GetPartySize() == 3)
    {
        LoadBgGraphic(1, gEquipCharacterSelect002, 1, 0, 0, 1);
        SetBgScrollFixed(1, 0, 0x100000);
        LoadBgGraphic(2, gEquipCharacterSelect003, 1, 0, 0, 0);
        SetBgScrollFixed(2, 0, 0xFFF60000);
    }
    else
    {
        g_pCombatResultBg1Tilemap = LoadBgGraphicTiles(1, gEquipCharacterSelect002, 1, 0);
        SetBgScrollFixed(1, 0, 0);
        g_pCombatResultBg2Tilemap = LoadBgGraphicTiles(2, gEquipCharacterSelect003, 1, 0);
        SetBgScrollFixed(2, 0, 0);

        if (GetPartySize() == 2)
        {
            COPY_PORTRAIT(1, g_pCombatResultBg1Tilemap, g_aCombatResultBg1PortraitRects, g_aCombatResultBg1PortraitPositions, 0, 0);
            COPY_PORTRAIT(1, g_pCombatResultBg1Tilemap, g_aCombatResultBg1PortraitRects, g_aCombatResultBg1PortraitPositions, 1, 1);
            COPY_PORTRAIT(2, g_pCombatResultBg2Tilemap, g_aCombatResultBg2PortraitRects, g_aCombatResultBg2PortraitPositions, 0, 0);
            COPY_PORTRAIT(2, g_pCombatResultBg2Tilemap, g_aCombatResultBg2PortraitRects, g_aCombatResultBg2PortraitPositions, 1, 1);
            SetBgScrollFixed(2, 0, 0xFFFE0000);
        }
        else
        {
            COPY_PORTRAIT(1, g_pCombatResultBg1Tilemap, g_aCombatResultBg1PortraitRects, g_aCombatResultBg1PortraitPositions, 2, 2);
            COPY_PORTRAIT(2, g_pCombatResultBg2Tilemap, g_aCombatResultBg2PortraitRects, g_aCombatResultBg2PortraitPositions, 2, 2);
            SetBgScrollFixed(2, 0, 0xFFFE0000);
            SetBgScrollFixed(1, g_abCombatResultPortraitScrollX[g_abCombatResultPartySlots[2]] << 16, 0);
        }
    }

    EnableBg(1);
    EnableBg(2);
    SetBgControl(0, g_dwCombatResultBg0Control);
    ClearBgTilemap(0);
    InitializeCombatResultXp();
    ReserveObjPaletteSlot(0);
    sub_0800D254((void *)GRAPHIC_BLOB_PALETTE_COLORS(gEquipCharacterSelect001), 0, 0x10);
    sub_0801493C();
    SetAlphaBlendTargets(4, 0x1F);
    SetAlphaBlendCoefficients(9, 7);
    PlayScreenTransitionInByIndex(0x3F, 2);

    g_dwCombatResultUnusedCounter = 0;
    g_dwCombatResultUnusedDelay = 0x78;
    g_GameModeStackContext.dwModeState = CombatResultStateIntroDelay;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
    g_GameModeStackContext.dwModeTimer = 0x3C;
}
