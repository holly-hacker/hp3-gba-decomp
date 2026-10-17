#include "types.h"
#include "battle/battle.h"
#include "combat_2.h"
#include "modes.h"

// Party-side counterpart to InitMonsterBattleActor: allocates the fighter's
// Actor, hardwires pActor->pfnTick = TickPlayerActionState, then populates
// the BattleFighter from g_aPartyMasterStats (Harry/Hermione/Ron) or from
// hardcoded values (Buckbeak). See docs/memory-map/battle.md.
Actor *InitPlayerBattleActor(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex)
{
    Actor *pActor;
    u8 type = fighterType;
    u8 slot = battleSlotIndex;
    u8 i;
    u16 hp;
    s32 posY;
    u8 **ppAnimCursor;

    pActor = AllocDefaultActor();
    pActor->wActorType = type;
    pActor->bUnk_0x7C = 0;

    pActor->oam.priority = 1;
    posY = slot * 0x40000 + 0x6E0000;
    SnapActorPosition(pActor, 0, posY);
    StartActorMove(pActor, (0xD4 - slot * 9 * 4) << 16, posY, 0x19);
    SetActorOrbitY(pActor, 0, 0x400, 0xC);

    pActor->bDepthSortBias = 0x40;
    pActor->nMoveSpeed = 1;
    pActor->dwFlags = 0x20006011;

    SetActorActionState(pActor, 0xF);

    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickPlayerActionState;
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

    fighter->pActor = pActor;

    if (g_PrevGameModeStackContext.dwCurrentGameMode != FolioUniversitas)
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
            fighter->bAgility = g_aPartyMasterStats[type].bAgility;
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
            fighter->bAgility = 10;
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
        AttachActorPaletteUnshared(pActor, g_aFighterAnimTable[type].aRecords[8].pPalette);
        SetActorAssetRecord(pActor, &g_aFighterAnimTable[type].aRecords[8]);
        SetActorAnimFrame(pActor, 8);
        SetActorActionState(pActor, 0);
        pActor->bActionFlags = hp;  // hp == 0 on this path; keeps hp in sb
        pActor->dwFlags &= ~0x10;
        SnapActorPosition(pActor, (0xD4 - slot * 9 * 4) << 16, slot * 0x40000 + 0x6E0000);
        fighter->nFaintedFlag = -1;
    }
    else
    {
        AttachActorPaletteUnshared(pActor, g_aFighterAnimTable[type].aRecords[0].pPalette);
        SetActorAnimData(pActor, &g_aFighterAnimTable[type], g_aFighterAnimDataTable[type][0], 0);
        // Via a temp: storing the field directly recolors the function.
        // The [0] reload folds back onto the base register, no extra move.
        ppAnimCursor = &pActor->anim.pAnimFrameCursor;
        *ppAnimCursor = pActor->anim.pAnimFrameBase + slot * 4 + 2;
        SetActorAnimFrame(pActor, (*ppAnimCursor)[0]);
    }
    return pActor;
}
