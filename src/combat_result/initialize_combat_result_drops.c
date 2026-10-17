#include "types.h"
#include "actor.h"
#include "font.h"
#include "text.h"
#include "items.h"
#include "game/rewards.h"
#include "game_state.h"
#include "sound.h"
#include "battle/battle.h"
#include "combat_result.h"

// Draws the drop phase: the Sickles earned (25% more with ForceItemDrop) and up
// to two dropped items, each granted to the player with its icon and name.
void InitializeCombatResultDrops(void)
{
    u8 *pText;
    s32 item0;
    s32 item1;
    const void *pPalette;
    const void *pTiles;
    const void *pFrames;

    SelectTextFont(3, 0, -1);
    pText = GetDialogText(0x527);  // "You are victorious!"
    g_wCombatResultTextTileCursor = DrawStringAligned(1, 0x78, 3, pText, 1);
    SelectTextFont(2, 0, -1);
    pText = GetDialogText(0x528);  // "The fleeing enemy dropped:"
    g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x78, 0x1C, pText, 1);

    if (g_nBattleGoldReward != 0)
    {
        if (g_dwBattleRewardFlagsSnapshot & ForceItemDrop)
            g_nBattleGoldReward += g_nBattleGoldReward / 4;

        AddSickles(g_nBattleGoldReward);
        g_pCombatResultCoinActor = SpawnActor(0, 0x14, 0x28, g_CombatResultCoinAsset.pPalette);
        SetActorAssetRecord(g_pCombatResultCoinActor, &g_CombatResultCoinAsset);
        SetActorAnimFrame(g_pCombatResultCoinActor, 0);
        SelectTextFont(1, 0, -1);
        pText = GetDialogText(0x597);  // "Sickles:"
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x3F, 0x32, pText, 0);
        pText = GetDialogText(0x8F7);  // "@1"
        SetTextMacro1Number(g_nBattleGoldReward);
        g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x7D, 0x32, pText, 2);
        g_nBattleGoldReward = 0;
    }

    RollBattleItemDrops(&item0, &item1);
    if ((u32)item0 > REWARD_ID_GOLD)
    {
        item0 = item1;
        item1 = COMBAT_RESULT_NO_ITEM;
    }
    else if ((u32)item1 > REWARD_ID_GOLD)
        item1 = COMBAT_RESULT_NO_ITEM;

    // The last Folio Universitas card gets a fanfare.
    if (item0 == REWARD_ID_GOLD - 1)
        PlaySoundEffect_candidate(0x26);
    if (item1 == REWARD_ID_GOLD - 1)
        PlaySoundEffect_candidate(0x26);

    g_pCombatResultItem0Actor = NULL;
    g_pCombatResultItem1Actor = NULL;
    if ((u32)item0 <= REWARD_ID_GOLD)
    {
        GrantReward(item0, 1);
        GetItemImageData(item0, &pPalette, &pTiles, &pFrames);
        g_pCombatResultItem0Actor = SpawnActor(0, 0x21, 0x50, pPalette);
        g_CombatResultItem0Gfx.pTileGfx = (void *)pTiles;
        g_CombatResultItem0Gfx.pFrameData = (void *)pFrames;
        SetActorAssetRecord(g_pCombatResultItem0Actor, &g_CombatResultItem0Gfx);
        SetActorAnimFrame(g_pCombatResultItem0Actor, 0);
        pText = GetDialogText(GetRewardNameStringId_candidate(item0));
        g_wCombatResultTextTileCursor = PrintTextBox(g_wCombatResultTextTileCursor, 0x3F, 0x48, 0x9C, pText, 0);

        if ((u32)item1 <= REWARD_ID_GOLD)
        {
            GrantReward(item1, 1);
            GetItemImageData(item1, &pPalette, &pTiles, &pFrames);
            g_pCombatResultItem1Actor = SpawnActor(0, 0x21, 0x70, pPalette);
            g_CombatResultItem1Gfx.pTileGfx = (void *)pTiles;
            g_CombatResultItem1Gfx.pFrameData = (void *)pFrames;
            SetActorAssetRecord(g_pCombatResultItem1Actor, &g_CombatResultItem1Gfx);
            SetActorAnimFrame(g_pCombatResultItem1Actor, 0);
            pText = GetDialogText(GetRewardNameStringId_candidate(item1));
            g_wCombatResultTextTileCursor = PrintTextBox(g_wCombatResultTextTileCursor, 0x3F, 0x68, 0x9C, pText, 0);
        }
    }

    pText = GetDialogText(0x647);  // "Press the A Button to continue."
    g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x78, 0x94, pText, 1);
}
