#include "types.h"
#include "battle.h"
#include "game_modes.h"

extern void sub_08030824(void);
extern Object *AllocObjectOfType(s32 type);
extern void SetObjectPosition(Object *obj, s32 x, s32 y);
extern void *AllocZeroed(u32 size);
extern void sub_0800EBAC(void);
extern void sub_0800F16C(void);
extern void SetupBattleRoster_candidate(void);
extern u8 *sub_08012AC0(void);
extern void sub_08007800(u8 *a, s32 b, s32 c);
extern void sub_0800F5F0(void);
extern void PlayMusicModule(u8 moduleId);

// Battle-message icon object (shown alongside ShowBattleMessage's text),
// distinct from the 7 per-fighter Objects in g_apFighterObjects_candidate.
extern Object *g_pBattleMessageIconObject_candidate;  // 0x03002684
extern u32 g_bSelectedFighterSlot_candidate;          // 0x03002660

// bIndex/dwParam are adjacent globals (0x03002688/0x0300268C) accessed
// through one base address in the real code, hence one struct here.
typedef struct {
    u8 bIndex;    // sentinel 0xFF = none pending
    u8 pad[3];
    u32 dwParam;
} BattleMessageIconState;
extern BattleMessageIconState g_BattleMessageIconState_candidate;  // 0x03002688

extern u8 g_abBattleMusicByRoom[];          // 0x0804E254, indexed by g_bCurrentRoomId
extern u8 g_abBattleMusicByOverworldSlot[]; // 0x0804E28B, indexed by dwCurrentGameModeArg1_candidate
// Read here as a full word, not the byte docs/memory-map/game_modes.md's
// plate comment describes elsewhere -- real source likely declares it int.
extern u32 g_bCurrentRoomId;                // 0x03003B50

// dwCurrentGameModeArg1_candidate (+4) and dwStoryStageCache_candidate (+0xC)
// are accessed through one shared base register in the real code, hence one
// struct here rather than two standalone globals.
typedef struct {
    u32 dwCurrentGameMode;               // 0x00 (0x03003EF4)
    u32 dwCurrentGameModeArg1_candidate; // 0x04
    u8 pad_08[0x0C - 0x08];
    u32 dwStoryStageCache_candidate;     // 0x0C; see docs/formats/save.md's abQuestEventState index 0
} GameModeStackContext_candidate;
extern GameModeStackContext_candidate g_GameModeStackContext_candidate;  // 0x03003EF4
extern BattleFighter g_aPartyMasterStats[]; // 0x030024EC, 0x48 stride, by FighterType
extern u16 g_nXpAccum;   // 0x0300260E
extern u16 g_nGoldAccum; // 0x03002610

// Battle mode's pInitFn. See docs/memory-map/battle.md.
void InitializeBattle(void)
{
    s32 i;
    u8 *uVar7;
    s32 slot;
    Object *pIconObj;
    u8 flagsBeforeSet;
    s32 flagsBeforeClear;
    s32 clearMask;

    sub_08030824();
    g_BattleMessageIconState_candidate.bIndex = 0xFF;
    g_BattleMessageIconState_candidate.dwParam = 0;
    g_dwBattleRewardFlagsSnapshot = 0;

    // Allocate all 6 fighter objects (3 on the player side, 3 on the enemy side)
    for (i = 0, slot = 0x90; i <= 6; i++)
    {
        g_apFighterObjects_candidate[i] = AllocObjectOfType(i + 0xE);
        SetObjectPosition(g_apFighterObjects_candidate[i], i * 0x16 + 0x60, 0x8A);
        g_apFighterObjects_candidate[i]->dwFlags = 0x20000008;
        g_apFighterObjects_candidate[i]->bUnk16 = 0x80;
        g_apFighterObjects_candidate[i]->bGfxSlotAndFlags =
            (g_apFighterObjects_candidate[i]->bGfxSlotAndFlags & 0xF) | slot;
        slot += 0x10;
    }

    g_pBattleMessageIconObject_candidate = AllocObjectOfType(i + 0xE);
    g_bSelectedFighterSlot_candidate = 0;
    SetObjectPosition(g_pBattleMessageIconObject_candidate, i * 0x16 + 0x60, 0x8A);
    pIconObj = g_pBattleMessageIconObject_candidate;
    pIconObj->dwFlags = 0x20000008;
    // Via a u8 *, not the struct field -- avoids a dead bit-field-store insn
    // that ties this constant's live range with dwFlags' in agbcc's register
    // allocator (see match-function skill, bucket 9).
    *(u8 *)&pIconObj->bUnk16 = 0x80;

    flagsBeforeSet = g_pBattleMessageIconObject_candidate->bFlags_0xD1;
    g_pBattleMessageIconObject_candidate->bFlags_0xD1 = flagsBeforeSet | 0x20;

    // The reload must come before clearMask is materialized -- picks the same
    // register pairing the ROM uses.
    flagsBeforeClear = g_pBattleMessageIconObject_candidate->bFlags_0xD1;
    clearMask = ~0xC;
    clearMask &= flagsBeforeClear;
    g_pBattleMessageIconObject_candidate->bFlags_0xD1 = clearMask;

    SetObjectPosition(g_pBattleMessageIconObject_candidate, 2, 0x75);

    for (i = 0; i < 4; i++)
        g_anFaintedRosterIndices[i] = -1;

    if (g_PrevGameModeCtx.dwMode != FolioUniversitas && g_PrevGameModeCtx.dwMode != HelpTopicScreen)
    {
        // entered new battle
        g_nXpAccum = 0;
        g_nGoldAccum = 0;
        g_pFightState = AllocZeroed(0x14C8);
        g_pFightState->pFighters = AllocZeroed(0x1F8);
        g_pFightState->pStagingFighters = AllocZeroed(0x1F8);
        g_pFightState->pPendingFighters_candidate = AllocZeroed(0xD8);

        if (g_aPartyMasterStats[0].bLevel == 0)
            g_pFightState->bEnemyScalePercent_candidate = 0x40;
        else if (g_aPartyMasterStats[0].bLevel < 2)
            g_pFightState->bEnemyScalePercent_candidate = 0x30;
        else
            g_pFightState->bEnemyScalePercent_candidate = 0x20;

        g_pFightState->bUnk106E = 0;
        sub_0800EBAC();
        SetupBattleRoster_candidate();
        uVar7 = sub_08012AC0();
        sub_08007800(uVar7, 0, 0x10);
        sub_0800F5F0();
    }
    else
    {
        // entered battle mode by exiting Folio Universitas or the Help screen, ie. this is not a new battle
        sub_0800EBAC();
        sub_0800F16C();
        uVar7 = sub_08012AC0();
        sub_08007800(uVar7, 0, 0x10);
        sub_0800F5F0();
    }

    if (g_GameModeStackContext_candidate.dwStoryStageCache_candidate == 0xFF)
        PlayMusicModule(g_abBattleMusicByOverworldSlot[g_GameModeStackContext_candidate.dwCurrentGameModeArg1_candidate]);
    else
        PlayMusicModule(g_abBattleMusicByRoom[g_bCurrentRoomId]);

    g_pFightState->bPendingStatusMessageVariant_candidate = 0x12;
}
