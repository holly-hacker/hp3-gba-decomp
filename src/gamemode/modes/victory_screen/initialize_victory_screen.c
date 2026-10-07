#include "types.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/rewards.h"
#include "battle/battle.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "battle/victory_screen.h"
#include "gen/graphics/menus.h"

// Copies the portrait of the party member in stats slot g_abVictoryPartySlots[partyPos]
// from the loaded BG graphic to the screen position of portrait index pos.
#define COPY_PORTRAIT(bg, pTilemap, rects, positions, partyPos, pos)                              \
    sub_08006C00(bg, pTilemap, 1, 0, rects[g_abVictoryPartySlots[partyPos]].bSrcX,                \
                 rects[g_abVictoryPartySlots[partyPos]].bSrcY, positions[pos].bDstX,              \
                 positions[pos].bDstY, rects[g_abVictoryPartySlots[partyPos]].bWidth,             \
                 rects[g_abVictoryPartySlots[partyPos]].bHeight)

void InitializeVictoryScreen(void)
{
    volatile u16 zero;
    u32 xp;
    u32 flags;

    g_wVictoryUnk2734 = 0;
    g_dwVictoryUnk26F4 = 0;
    g_dwVictoryUnk26F8 = 0;
    g_dwVictoryUnk26FC = 0;

    g_dwVictoryXpRemaining = xp = g_nBattleXpReward;
    flags = g_dwBattleRewardFlagsSnapshot;
    if (flags & ExtraExpBonus)
        g_dwVictoryXpRemaining = xp * 3;

    if (flags & GrantExtraXp)
        g_dwVictoryXpRemaining = g_dwVictoryXpRemaining * 3 / 2;

    if (GetPartySize() == 3)
    {
        g_abVictoryPartySlots[0] = 1;
        g_abVictoryPartySlots[1] = 2;
        g_abVictoryPartySlots[2] = 0;
    }
    else if (GetPartySize() == 2)
    {
        g_abVictoryPartySlots[0] = GetPartyMasterStatsSlot_candidate(g_bPartyCharId0);
        g_abVictoryPartySlots[1] = GetPartyMasterStatsSlot_candidate(g_bPartyCharId1);
    }
    else if (GetPartySize() == 1)
    {
        g_abVictoryPartySlots[2] = GetPartyMasterStatsSlot_candidate(g_bPartyCharId0);
    }

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(3, g_dwVictoryBg3Control);
    ClearBgTilemap(3);
    LoadBgGraphic(3, gEquipCharacterSelect001, 1, 0, 0, 0);
    SetBgControl(1, g_dwVictoryBg1Control);
    ClearBgTilemap(1);
    SetBgControl(2, g_dwVictoryBg2Control);
    ClearBgTilemap(2);

    if (GetPartySize() == 3)
    {
        LoadBgGraphic(1, gEquipCharacterSelect002, 1, 0, 0, 1);
        sub_08007AF0(1, 0, 0x100000);
        LoadBgGraphic(2, gEquipCharacterSelect003, 1, 0, 0, 0);
        sub_08007AF0(2, 0, 0xFFF60000);
    }
    else
    {
        g_pVictoryBg1Tilemap = LoadBgGraphicTiles_candidate(1, gEquipCharacterSelect002, 1, 0);
        sub_08007AF0(1, 0, 0);
        g_pVictoryBg2Tilemap = LoadBgGraphicTiles_candidate(2, gEquipCharacterSelect003, 1, 0);
        sub_08007AF0(2, 0, 0);

        if (GetPartySize() == 2)
        {
            COPY_PORTRAIT(1, g_pVictoryBg1Tilemap, g_aVictoryBg1PortraitRects, g_aVictoryBg1PortraitPositions, 0, 0);
            COPY_PORTRAIT(1, g_pVictoryBg1Tilemap, g_aVictoryBg1PortraitRects, g_aVictoryBg1PortraitPositions, 1, 1);
            COPY_PORTRAIT(2, g_pVictoryBg2Tilemap, g_aVictoryBg2PortraitRects, g_aVictoryBg2PortraitPositions, 0, 0);
            COPY_PORTRAIT(2, g_pVictoryBg2Tilemap, g_aVictoryBg2PortraitRects, g_aVictoryBg2PortraitPositions, 1, 1);
            sub_08007AF0(2, 0, 0xFFFE0000);
        }
        else
        {
            COPY_PORTRAIT(1, g_pVictoryBg1Tilemap, g_aVictoryBg1PortraitRects, g_aVictoryBg1PortraitPositions, 2, 2);
            COPY_PORTRAIT(2, g_pVictoryBg2Tilemap, g_aVictoryBg2PortraitRects, g_aVictoryBg2PortraitPositions, 2, 2);
            sub_08007AF0(2, 0, 0xFFFE0000);
            sub_08007AF0(1, g_abVictoryPortraitScrollX[g_abVictoryPartySlots[2]] << 16, 0);
        }
    }

    EnableBg(1);
    EnableBg(2);
    SetBgControl(0, g_dwVictoryBg0Control);
    ClearBgTilemap(0);
    sub_08013AC8();
    sub_0803094C(0);
    sub_0800D254((void *)GRAPHIC_BLOB_PALETTE_COLORS(gEquipCharacterSelect001), 0, 0x10);
    sub_0801493C();
    SetAlphaBlendTargets(4, 0x1F);
    SetAlphaBlendCoefficients(9, 7);
    PlayScreenTransitionInByIndex(0x3F, 2);

    g_dwVictoryUnk26E8 = 0;
    g_dwVictoryUnk26EC = 0x78;
    g_GameModeStackContext.dwModeState = VictoryStateIntroDelay;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
    g_GameModeStackContext.dwModeTimer = 0x3C;
}
