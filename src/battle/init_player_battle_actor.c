#include "types.h"
#include "battle.h"
#include "game_modes.h"

// Party-side counterpart to InitMonsterBattleActor: allocates the fighter's
// Object, hardwires pObject->pfnTick = TickPlayerActionState, then populates
// the BattleFighter from g_aPartyMasterStats (Harry/Hermione/Ron) or from
// hardcoded values (Buckbeak). See docs/memory-map/battle.md.
Object *InitPlayerBattleActor(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex)
{
    Object *pObject;
    u8 type = fighterType;
    u8 slot = battleSlotIndex;
    u8 i;
    u16 hp;
    s32 clearMask;
    s32 flagsBeforeClear;
    s32 posY;
    u8 **ppAnimCursor;

    pObject = AllocDefaultObject();
    pObject->wObjectType = type;
    pObject->bUnk_0x7C = 0;

    // Reload before the mask is materialized, and fold through the mask
    // itself: a separate dest pseudo ties to the loaded value in regmove
    // and steals r0 from the mask (same idiom as InitializeBattle).
    flagsBeforeClear = pObject->bGfxSlotAndFlags;
    clearMask = ~0xC;
    clearMask &= flagsBeforeClear;

    pObject->bGfxSlotAndFlags = clearMask | 4;
    posY = slot * 0x40000 + 0x6E0000;
    SnapObjectPosition(pObject, 0, posY);
    StartObjectMove(pObject, (0xD4 - slot * 9 * 4) << 16, posY, 0x19);
    sub_08003A44(pObject, 0, 0x400, 0xC);

    pObject->bUnk16 = 0x40;
    pObject->dwUnk_0x28 = 1;
    pObject->dwFlags = 0x20006011;

    SetFighterAttackAnimState_candidate(pObject, 0xF);

    pObject->bAnimFrameDelay = 1;
    pObject->pfnTick = TickPlayerActionState;
    fighter->bFighterType = type;

    if (type < 3)
    {
        fighter->bKnownSpellCount = g_aPartyMasterStats[type].bKnownSpellCount;
        i = 0;
        do
        {
            fighter->aSpellCastLevel[i] = g_aPartyMasterStats[type].aSpellCastLevel[i];
            fighter->aSpellUsageProgress[i] = g_aPartyMasterStats[type].aSpellUsageProgress[i];
            i++;
        } while (i <= 9);
    }

    fighter->pObject = pObject;

    if (g_PrevGameModeCtx.dwCurrentGameMode != FolioUniversitas)
    {
        fighter->bSlotParam = slot;
        fighter->bSelectedActionIndex = 0xFF;

        if (type < 3)
        {
            fighter->bLevel = g_aPartyMasterStats[type].bLevel;
            fighter->wHp = g_aPartyMasterStats[type].wHp;
            fighter->wHp_max = g_aPartyMasterStats[type].wHp_max;
            fighter->wMp = g_aPartyMasterStats[type].wMp;
            fighter->wMp_max = g_aPartyMasterStats[type].wMp_max;
            fighter->bSpeed = g_aPartyMasterStats[type].bSpeed;
            fighter->bAccuracy = g_aPartyMasterStats[type].bAccuracy;
            fighter->bDefenseFactorPercent = g_aPartyMasterStats[type].bDefenseFactorPercent;
            fighter->bMagicDefensePercent = g_aPartyMasterStats[type].bMagicDefensePercent;
            fighter->wRewardXp = g_aPartyMasterStats[type].wRewardXp;
            fighter->bStatusFlags = StatusNone;
            fighter->nFaintedFlag = 0;
            fighter->unk3E |= 0xFF;
        }
        else
        {
            u8 *partyBase;

            // Buckbeak stats
            fighter->bLevel = 50;
            fighter->wHp = 400;
            fighter->wHp_max = 400;
            fighter->wMp = 999;
            fighter->wMp_max = 999;
            fighter->bSpeed = 10;
            fighter->bAccuracy = 101;
            fighter->bDefenseFactorPercent = 100;
            fighter->bMagicDefensePercent = 100;
            fighter->wRewardXp = 0;
            fighter->bStatusFlags = StatusNone;
            fighter->nFaintedFlag = 0;
            fighter->unk3E |= 0xFF;

            // Back up into slot 3, past the three party entries; via a
            // temp because &g_aPartyMasterStats[3] folds to one ldr.
            partyBase = (u8 *)g_aPartyMasterStats;
            memcpy(partyBase + 3 * sizeof(BattleFighter), fighter, sizeof(BattleFighter));
        }
    }

    hp = fighter->wHp;

    if (hp == 0)
    {
        AttachObjectEffectSlot_candidate(pObject, g_aFighterAnimTable[type].nEffectSlotFainted);
        SetObjectAssetRecord(pObject, &g_aFighterAnimTable[type].pAssetRecordFainted);
        sub_08001958(pObject, 8);
        SetFighterAttackAnimState_candidate(pObject, 0);
        pObject->bActionFlags = hp;  // hp == 0 on this path; keeps hp in sb
        pObject->dwFlags &= ~0x10;
        SnapObjectPosition(pObject, (0xD4 - slot * 9 * 4) << 16, slot * 0x40000 + 0x6E0000);
        fighter->nFaintedFlag = -1;
    }
    else
    {
        AttachObjectEffectSlot_candidate(pObject, g_aFighterAnimTable[type].nEffectSlotLive);
        SetObjectAnimData(pObject, &g_aFighterAnimTable[type], &g_aFighterAnimDataTable[type * 0x244], 0);
        // Via a temp: storing the field directly recolors the function.
        // The [0] reload folds back onto the base register, no extra move.
        ppAnimCursor = &pObject->pAnimFrameCursor;
        *ppAnimCursor = pObject->pAnimFrameBase + slot * 4 + 2;
        sub_08001958(pObject, (*ppAnimCursor)[0]);
    }
    return pObject;
}
