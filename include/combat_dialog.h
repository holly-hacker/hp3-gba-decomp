#pragma once

#include "combat.h"
#include "constants/spells.h"
#include "video.h"

// ShowBattleMessage's code. Its value and param: SpecialMoveAnnounce and SpecialAbilityText
// take the Special Move in value; AttackResult the damage (or, for param 2, the fainted
// fighter's index) and the result variant in param; PotionUseAnnounce and StatusRestore the
// potion; SpCost and MpCost the amount; HiddenFromView value 1 to clear the box first
// and the fighter index in param.
typedef enum {
    SpellLevelUp      = 0,
    EscapeBlocked     = 1,
    SpecialMoveAnnounce = 2,
    SpecialAbilityText = 3,
    ActionAnnounce    = 4,
    AttackResult      = 5,
    FaintResult       = 6,
    PotionUseAnnounce = 7,
    StatusRestore     = 8,
    SpCost            = 9,
    MpCost            = 10,
    Victory           = 11,
    Defeat            = 12,
    CantMove          = 13,
    CanMoveAgain      = 14,
    // Not AttackWeakened, which BattleStatusFlags already owns.
    AttackWeakenedMessage = 15,
    // Not Hidden, for the same reason.
    HiddenFromView    = 16,
    ImmuneToParalysis = 17,
} BattleMessageCode;
// bPendingStatusMessageVariant_candidate's "none" value, written at battle
// init: the guard at each ShowBattleMessage(AttackResult, 0, variant) site
// skips the second message while it holds.
#define NO_PENDING_STATUS_MESSAGE_VARIANT 0x12

// Top of each text row in the battle message box. The Japanese font's rows are taller.
#ifdef VERSION_JP
#define BATTLE_TEXT_ROW0_Y 199
#define BATTLE_TEXT_ROW1_Y 209
#define BATTLE_TEXT_ROW2_Y 219
#define BATTLE_TEXT_ROW3_Y 228
#else
#define BATTLE_TEXT_ROW0_Y 200
#define BATTLE_TEXT_ROW1_Y 208
#define BATTLE_TEXT_ROW2_Y 216
#define BATTLE_TEXT_ROW3_Y 224
#endif

extern void TickBattleMenuInput(void);
extern void OpenBattleTopMenu(u32 fighterIndex, u32 row);
extern void OpenSpecialMoveMenu(u8 fighterIndex);
extern void OpenItemMenu(u8 fighterIndex);
extern void OpenSpellTierMenu(u8 fighterIndex, u8 spellRow);
extern void OpenAllyTargetMenu(u8 fighterIndex);
extern void ShowBattleMessage(u8 code, u16 value, u16 param);
extern void DrawBattleMenuText(void);
// Flash the targeted fighter's sprite palette: an enemy or ally target slot, or a fainted ally.
extern void FlashEnemyTarget(u32 slot);
extern void FlashAllyTarget(u32 slot);
extern void FlashFaintedAlly(u32 faintedIndex);
extern void HandleBattleVBlank(void);  // battle VBlank callback, set by InitBattleDisplay
extern void SetBattleMenuIconState(u32 kind, u32 row, u32 fighterType, u32 enabled);
extern void TickBattleMenuStub(void);  // does nothing; called by TickBattleMenuInput

// Label of each battle top menu row (Cast Spell, Special Move, Informus, Use Item, Flee,
// Folio Bruti, Help).
extern const u32 g_adwBattleTopMenuTextIds[7];  // 0x0804D808
extern const ActorAssetRecord g_aPartyFaceAssets[4];         // 0x0804D824
extern const ActorAssetRecord g_aMonsterFaceAssets[68];      // 0x0804D864
extern const ActorAssetRecord g_aBattleMenuIconAssets[61];   // 0x0804DCA4

extern const u32 g_dwBattleFloorBgControl;  // 0x0804E074, passed to InitFloorDisplay
extern const u32 g_dwBattleBg1Control;      // 0x0804E078
extern const u32 g_dwBattleBg0Control;      // 0x0804E07C, also the battle text target
extern const u32 g_dwBattleBgControlUnused_candidate;  // 0x0804E080, no reader found
// Spell id of each spell menu row, per party FighterType (Harry, Hermione, Ron).
extern const u8 g_aabFighterSpellMenu[3][7];  // 0x0804E084

typedef struct {
    const void *pFloor;  // graphic blob, see docs/formats/graphic_blob.md
    const void *pWall;
} BattleBackgroundPair;
extern const BattleBackgroundPair g_aBattleBackgroundPairs[55];  // 0x0804E09C, indexed by g_bCurrentRoomId

extern const u8 g_abBattleMusicByRoom[55];          // 0x0804E254, indexed by g_bCurrentRoomId
extern const u8 g_abBattleMusicByScriptedEncounter[15]; // 0x0804E28B, indexed by dwCurrentGameModeArg1 (scripted encounter id)

extern const ActorAssetRecord g_MenuSprite003Asset_candidate;  // 0x0804E29C, no reader found

// Battle screen scanline callbacks, copied to g_aBattleScanlineEffectBuffer by InitBattleDisplay,
// RestoreBattleScanlineEffects and ResetBattleDisplayEffects.
extern const ScanlineEffectEntry g_aBattleScanlineEffects[4];  // 0x0804E2AC

// TickBattleMenuInput calls the bMenuScreen entry of the confirm table on A and of the cancel
// table on B, passing the active fighter's FighterType and record.
typedef void (*BattleMenuInputHandler)(u32 fighterType, BattleFighter *pFighter);
extern const BattleMenuInputHandler g_apfnBattleMenuConfirmHandlers[11];  // 0x0804E2EC
extern const BattleMenuInputHandler g_apfnBattleMenuCancelHandlers[11];   // 0x0804E318

// Battle message text ids. The per-fighter tables hold the four party FighterTypes, then the
// 69 monsters from index 4.
extern const u32 g_adwFighterActionTextIds[73];      // 0x0804E344, "Harry casts a spell:", "... attacks!"
extern const u32 g_adwFighterFaintTextIds[73];       // 0x0804E468, "... falls unconscious!", "... goes away!"
extern const u32 g_adwSpecialMoveResultTextIds[16];  // 0x0804E58C, by ShowBattleMessage's variant
extern const u32 g_adwReviveTextIds[5];              // 0x0804E5CC, by FighterType; 4 = the whole party

extern const u8 g_abSpellMaxLevel[SPELL_COUNT];  // 0x0804E5E0, by spell id; caps TrackSpellFamiliarity
extern const u8 g_abSpellLevelUpThreshold[2];  // 0x0804E5EA, by cast level - 1
extern const u32 g_adwFighterCantMoveTextIds[4];  // 0x0804E5EC, by party FighterType
extern const u8 g_sBattleTextSpace[];             // 0x0804E5FC, " "

// The target flash palette effect's two frames: the sprite's own palette, then
// gTargetFlashPalette.
extern u16 g_aawTargetFlashPalette[2][16];

