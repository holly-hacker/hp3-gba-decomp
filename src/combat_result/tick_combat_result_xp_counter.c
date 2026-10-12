#include "types.h"
#include "actor.h"
#include "battle/battle.h"
#include "font.h"
#include "text.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "overworld/room_script.h"
#include "palette.h"
#include "combat_result.h"

#define FIGHTER(pos) g_aPartyMasterStats[g_abCombatResultPartySlots[pos]]
#define MAX_DISPLAY_LEVEL 98

// Counts one XP point off the pool. Each party member below level 99 loses one
// point of experience-to-next-level; at 0 they level up, which redraws their
// level and shows a sparkle and "Level Up!" over their column.
void TickCombatResultXpCounter(void)
{
    u8 *pText;
    s32 leftIconX;
    s32 rightIconX;
    s32 xpX;
    s32 clearTileX;
    u8 partySize;

    partySize = GetPartySize();
    xpX = g_wCombatResultXpNumberX;
    clearTileX = xpX / 8 - 1;
    if (partySize == 2)
    {
        leftIconX = 0x24;
        rightIconX = 0xC1;
    }
    else
    {
        leftIconX = 0x32;
        rightIconX = 0xBE;
    }

    g_dwCombatResultXpRemaining--;
    SelectTextFont(2, 0, -1);
    ClearBgTilemapRect(0, clearTileX, 0x12, 8, 2);
    pText = GetDialogText(0x8F7);  // "@1"
    SetTextMacro1Number(g_dwCombatResultXpRemaining);
    DrawStringAligned(g_wCombatResultXpTileCursor, xpX, 0x94, pText, 0);
    SelectTextFont(0, 0, -1);

    if (partySize > 1)
    {
        if (FIGHTER(0).bLevel <= MAX_DISPLAY_LEVEL)
        {
            Actor *pActor;

            FIGHTER(0).wRewardXp--;
            g_aCombatResultPartyRows[0].nXpToNextLevel--;
            if ((s16)FIGHTER(0).wRewardXp == 0)
            {
                PlaySoundEffect_candidate(0x1B);
                LevelUpPartyMember_candidate(g_abCombatResultPartySlots[0]);
                ClearBgTilemapRect(0, 7, 0xE, 3, 1);
                pText = GetDialogText(0x8F7);  // "@1"
                SetTextMacro1Number(FIGHTER(0).bLevel + 1);
                DrawStringAligned(g_aCombatResultPartyRows[0].wLevelTileCursor, 0x4C, 0x70, pText, 2);
                g_aCombatResultPartyRows[0].nXpToNextLevel = GetPartyMemberXpToNextLevel(g_abCombatResultPartySlots[0]);
                pActor = SpawnMenuIconActor(0, 0);
                SetActorPosition(pActor, leftIconX, 0x6E);
                pActor->dwFlags = ActorFlagVisible | ActorFlagHasAnimation;
                AttachActorPalette(pActor, g_CombatResultLevelUpSparkleAsset.pPalette);
                SetActorAnimData(pActor, &g_CombatResultLevelUpSparkleAsset, g_abCombatResultLevelUpSparkleAnim, 0);
                SetActorDrawLayer(pActor, 0);
                SelectTextFont(0, 6, -1);
                pText = GetDialogText(0x52E);  // "Level Up!"
                DrawStringAligned(g_aCombatResultPartyRows[0].wLevelUpTileCursor, 0x30, 0x5F, pText, 1);
            }

            SelectTextFont(0, 0, -1);
            pText = GetDialogText(0x8F7);  // "@1"
            SetTextMacro1Number(GetPartyMemberTotalXp(g_abCombatResultPartySlots[0]));
            ClearBgTilemapRect(0, 7, 0xD, 3, 1);
            DrawStringAligned(g_aCombatResultPartyRows[0].wExpTileCursor, 0x4C, 0x68, pText, 2);
            if (g_aCombatResultPartyRows[0].nXpToNextLevel < 0)
                g_aCombatResultPartyRows[0].nXpToNextLevel = 0;

            if (FIGHTER(0).bLevel <= MAX_DISPLAY_LEVEL)
            {
                ClearBgTilemapRect(0, 7, 0xF, 3, 1);
                SetTextMacro1Number(g_aCombatResultPartyRows[0].nXpToNextLevel);
                DrawStringAligned(g_aCombatResultPartyRows[0].wNextTileCursor, 0x4C, 0x78, pText, 2);
            }
            else
                ClearBgTilemapRect(0, 2, 0xF, 8, 1);
        }

        if (FIGHTER(1).bLevel <= MAX_DISPLAY_LEVEL)
        {
            Actor *pActor;

            FIGHTER(1).wRewardXp--;
            g_aCombatResultPartyRows[1].nXpToNextLevel--;
            if ((s16)FIGHTER(1).wRewardXp == 0)
            {
                PlaySoundEffect_candidate(0x1B);
                LevelUpPartyMember_candidate(g_abCombatResultPartySlots[1]);
                pText = GetDialogText(0x8F7);  // "@1"
                ClearBgTilemapRect(0, 0x19, 0xE, 3, 1);
                SetTextMacro1Number(FIGHTER(1).bLevel + 1);
                DrawStringAligned(g_aCombatResultPartyRows[1].wLevelTileCursor, 0xDC, 0x70, pText, 2);
                g_aCombatResultPartyRows[1].nXpToNextLevel = GetPartyMemberXpToNextLevel(g_abCombatResultPartySlots[1]);
                pActor = SpawnMenuIconActor(2, 0);
                SetActorPosition(pActor, rightIconX, 0x6E);
                pActor->dwFlags = ActorFlagVisible | ActorFlagHasAnimation;
                AttachActorPalette(pActor, g_CombatResultLevelUpSparkleAsset.pPalette);
                SetActorAnimData(pActor, &g_CombatResultLevelUpSparkleAsset, g_abCombatResultLevelUpSparkleAnim, 0);
                SetActorDrawLayer(pActor, 0);
                SelectTextFont(0, 6, -1);
                pText = GetDialogText(0x52E);  // "Level Up!"
                DrawStringAligned(g_aCombatResultPartyRows[1].wLevelUpTileCursor, 0xC1, 0x5F, pText, 1);
            }

            SelectTextFont(0, 0, -1);
            pText = GetDialogText(0x8F7);  // "@1"
            ClearBgTilemapRect(0, 0x19, 0xD, 3, 1);
            SetTextMacro1Number(GetPartyMemberTotalXp(g_abCombatResultPartySlots[1]));
            DrawStringAligned(g_aCombatResultPartyRows[1].wExpTileCursor, 0xDC, 0x68, pText, 2);
            if (g_aCombatResultPartyRows[1].nXpToNextLevel < 0)
                g_aCombatResultPartyRows[1].nXpToNextLevel = 0;

            if (FIGHTER(1).bLevel <= MAX_DISPLAY_LEVEL)
            {
                ClearBgTilemapRect(0, 0x19, 0xF, 3, 1);
                SetTextMacro1Number(g_aCombatResultPartyRows[1].nXpToNextLevel);
                DrawStringAligned(g_aCombatResultPartyRows[1].wNextTileCursor, 0xDC, 0x78, pText, 2);
            }
            else
                ClearBgTilemapRect(0, 0x14, 0xF, 8, 1);
        }
    }

    if (partySize != 2)
    {
        if (FIGHTER(2).bLevel <= MAX_DISPLAY_LEVEL)
        {
            Actor *pActor;

            FIGHTER(2).wRewardXp--;
            g_aCombatResultPartyRows[2].nXpToNextLevel--;
            if ((s16)FIGHTER(2).wRewardXp == 0)
            {
                PlaySoundEffect_candidate(0x1B);
                LevelUpPartyMember_candidate(g_abCombatResultPartySlots[2]);
                ClearBgTilemapRect(0, 0x10, 0xE, 3, 1);
                pText = GetDialogText(0x8F7);  // "@1"
                SetTextMacro1Number(FIGHTER(2).bLevel + 1);
                DrawStringAligned(g_aCombatResultPartyRows[2].wLevelTileCursor, 0x94, 0x70, pText, 2);
                g_aCombatResultPartyRows[2].nXpToNextLevel = GetPartyMemberXpToNextLevel(g_abCombatResultPartySlots[2]);
                pActor = SpawnMenuIconActor(1, 0);
                SetActorPosition(pActor, 0x7A, 0x6E);
                pActor->dwFlags = ActorFlagVisible | ActorFlagHasAnimation;
                AttachActorPalette(pActor, g_CombatResultLevelUpSparkleAsset.pPalette);
                SetActorAnimData(pActor, &g_CombatResultLevelUpSparkleAsset, g_abCombatResultLevelUpSparkleAnim, 0);
                SetActorDrawLayer(pActor, 0);
                SelectTextFont(0, 6, -1);
                pText = GetDialogText(0x52E);  // "Level Up!"
                DrawStringAligned(g_aCombatResultPartyRows[2].wLevelUpTileCursor, 0x78, 0x5F, pText, 1);
            }

            SelectTextFont(0, 0, -1);
            pText = GetDialogText(0x8F7);  // "@1"
            ClearBgTilemapRect(0, 0x10, 0xD, 3, 1);
            SetTextMacro1Number(GetPartyMemberTotalXp(g_abCombatResultPartySlots[2]));
            DrawStringAligned(g_aCombatResultPartyRows[2].wExpTileCursor, 0x94, 0x68, pText, 2);
            if (g_aCombatResultPartyRows[2].nXpToNextLevel < 0)
                g_aCombatResultPartyRows[2].nXpToNextLevel = 0;

            if (FIGHTER(2).bLevel <= MAX_DISPLAY_LEVEL)
            {
                ClearBgTilemapRect(0, 0x10, 0xF, 3, 1);
                SetTextMacro1Number(g_aCombatResultPartyRows[2].nXpToNextLevel);
                DrawStringAligned(g_aCombatResultPartyRows[2].wNextTileCursor, 0x94, 0x78, pText, 2);
            }
            else
                ClearBgTilemapRect(0, 0xB, 0xF, 8, 1);
        }
    }
}
