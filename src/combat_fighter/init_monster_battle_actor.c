#include "types.h"
#include "combat_fighter.h"

// Monster-side counterpart to InitPlayerBattleActor: allocates the fighter's
// Actor, hardwires pActor->pfnTick = TickFighterAttackAnimState_candidate,
// then populates the BattleFighter from MonsterTable. See docs/memory-map/battle.md.

#define BATTLE_SLOT_ORIGIN_X 204
#define BATTLE_SLOT_ORIGIN_Y 78

Actor *InitMonsterBattleActor(BattleFighter *fighter, s32 monsterIndex, s32 battleSlotIndex)
{
    Actor *pActor;
    u8 type = monsterIndex;
    u8 slot = battleSlotIndex;
    s32 xBase;
    s32 actorType;
    s32 slotX2;
    Actor *pShadowActor;
    u8 **ppAnimCursor;
    u8 **ppBase;

    pActor = AllocDefaultActor();
    actorType = type + 4;
    pActor->wActorType = actorType;
    pActor->bUnk_0x7C = 0;

    // Slot anchor in pixels, stored 16.16; the move target reuses X + 24.
    xBase = slot * 36;
    SnapActorPosition(pActor, (xBase + BATTLE_SLOT_ORIGIN_X) << 16, (BATTLE_SLOT_ORIGIN_Y - slot * 4) << 16);
    StartActorMove(pActor, (xBase + 24) << 16, (BATTLE_SLOT_ORIGIN_Y - slot * 4) << 16, 0x1E);

    SetActorOrbitY(pActor, 0, 0x400, -0xC);

    pActor->oam.priority = 1;
    pActor->bDepthSortBias = -0x40;
    pActor->nMoveSpeed = 1;
    pActor->dwFlags = 0x20006019;

    SetActorActionState(pActor, 0xF);

    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickFighterAttackAnimState_candidate; // contains `Mt19937RandMax` call every enemy turn to determine target

    AttachActorPaletteUnshared(pActor, g_pMonsterGraphicsTable[type].battle.pPalette);
    SetActorAnimData(pActor, &g_pMonsterGraphicsTable[type].battle, g_pMonsterAnimFrameTable[type], 0);

    ppAnimCursor = &pActor->anim.pAnimFrameCursor;
    ppBase = &pActor->anim.pAnimFrameBase;

    // Doubling as slot + slot: slot * 2 splits the copy and shift across
    // r3/r0, this keeps both in r0.
    slotX2 = slot + slot;

    *ppAnimCursor = *ppBase + slotX2 + 2;
    if (slot > 4)
        *ppAnimCursor = *ppBase + 2;

    SetActorAnimFrame(pActor, **ppAnimCursor);

    // certain flying monsters? Cornish Pixie, Bat, Dragonfly
    if (type == 3 || type == 0x1D || type == 0x1A)
    {
        s32 slot64 = slot * 64;
        SetActorOrbitX(pActor, slot64, 0x800, 2);
        SetActorOrbitY(pActor, slot64, 0x800, 2);
    }
    // fire effect monsters? Salamander, Amazonian Salamander, Peruvian Salamander
    else if ((u8)(type - 0x2D) <= 2)
    {
        pShadowActor = AllocDefaultActor();
        pShadowActor->wActorType = actorType;
        pShadowActor->bUnk_0x7C = 0;

        SetActorOrbitY(pShadowActor, 0, 0x400, -0xC);

        pShadowActor->oam.priority = 1;
        pShadowActor->bDepthSortBias = -0x40;
        pShadowActor->nMoveSpeed = 1;
        pShadowActor->dwFlags = 0x6019;
        pShadowActor->anim.bAnimFrameDelay = 1;

        AttachActorPalette(pShadowActor, g_MonsterShadowGfxRow.pPalette);
        SetActorAnimData(pShadowActor, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, 0);

        pShadowActor->anim.pAnimFrameCursor = pShadowActor->anim.pAnimFrameBase + slotX2 + 2;

        if (slot > 4)
            pShadowActor->anim.pAnimFrameCursor = pShadowActor->anim.pAnimFrameBase + 2;

        SetActorAnimFrame(pShadowActor, pShadowActor->anim.pAnimFrameCursor[0]);

        pShadowActor->pOwnerActor = pActor;
        pActor->pShadowActor = pShadowActor;
    }
    fighter->bFighterType = Enemy;
    fighter->pActor = pActor;
    fighter->stats.wHp = MonsterTable[type].wHp;
    fighter->wHp_max = MonsterTable[type].wHp;
    fighter->bAgility = MonsterTable[type].bAgility;
    fighter->bAccuracy = MonsterTable[type].bAccuracy;
    fighter->bCritChance = MonsterTable[type].bCritChance;
    fighter->wDamageRollMin = MonsterTable[type].wDamageMin;
    fighter->wDamageRollMax = MonsterTable[type].wDamageMax;

    fighter->bEffectivenessFlipendo = MonsterTable[type].abEffectiveness[0];
    fighter->bEffectivenessIncendio = MonsterTable[type].abEffectiveness[1];
    fighter->bEffectivenessVerdimillious = MonsterTable[type].abEffectiveness[2];
    fighter->bEffectivenessWingardiumLeviosa = MonsterTable[type].abEffectiveness[3];
    fighter->bEffectivenessGlacius = MonsterTable[type].abEffectiveness[4];
    fighter->bEffectivenessDiffindo = MonsterTable[type].abEffectiveness[5];

    fighter->stats.wRewardXp = MonsterTable[type].wRewardXp;
    fighter->stats.bLevel = MonsterTable[type].bLevel;
    fighter->wRewardGold = MonsterTable[type].wRewardGold;
    fighter->bStatusFlags = StatusNone;
    fighter->nFaintedFlag = 0;
    fighter->bRosterIndex = type;
    fighter->unk3E = -1;
    fighter->bSlotParam = slot;

    return pActor;
}
