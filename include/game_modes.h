#pragma once

#include "types.h"

// See docs/memory-map/game_modes.md. Index 0 into g_pGameModeDispatchTable
// is unused/reserved -- there is no GameMode value 0.
typedef enum {
    Startup                          = 0x01,
    LanguageSelect                   = 0x02,
    MainMenu                         = 0x03,
    LoadGame                         = 0x04,
    Options                          = 0x05,
    MinigameMenu                     = 0x06,
    NewGameMenu                      = 0x07,
    Overworld                        = 0x08,
    Battle                           = 0x09,
    InGameMenu                       = 0x0A,
    InGameMenuFadeIn                 = 0x0B,
    StatusEquipCharacterSelect_0xC   = 0x0C,
    StatusEquipCharacterSelect_0xD   = 0x0D,
    StatusEquipHarry                 = 0x0E,
    StatusEquipHarryItemSelect       = 0x0F,
    ItemsSectionSelect               = 0x10,
    ItemsItemSelect                  = 0x11,
    ItemUseScreen                    = 0x12,
    Folios                           = 0x13,
    GameSave                         = 0x14,
    CardTrade                        = 0x15,
    Connectivity                     = 0x16,
    Help                             = 0x17,
    Dialogue                         = 0x18,
    DebugMenuMain                    = 0x19,
    LoadingScreen                      = 0x1A,
    WizardCrackerPopItMinigame       = 0x1B,
    DivinationTeaMinigame            = 0x1C,
    HighScoreNameEntryUnused         = 0x1D,
    MinigameDifficultySelect         = 0x1E,
    DebugMenuMapSelect               = 0x1F,
    DebugMenuLevelAndQuestSelect     = 0x20,
    DebugMenuSoundTest               = 0x21,
    DebugMenuCollectorCards          = 0x22,
    DebugMenuPortraits               = 0x23,
    UnusedServePumpkinJuiceMinigame  = 0x24,
    UnusedHogwartsMapScreen          = 0x25,
    FolioUniversitas                 = 0x26,
    CoolTrainCutscene                = 0x27,
    FolioUniversitasCardDetails      = 0x28,
    OwlCareMinigame                  = 0x29,
    DebugMenuCharacterSelect         = 0x2A,
    HippogriffGlideMinigame          = 0x2B,
    VictoryScreen                    = 0x2C,
    FolioBruti                       = 0x2D,
    FredAndGeorgesShop               = 0x2E,
    RiddikulusMinigame               = 0x2F,
    ClockSkipCutscene                = 0x30,
    HogwartsUpNightCutscene          = 0x31,
    PurpleScreenReturnToMenu         = 0x32,
    HarryVsDementorsMinigame         = 0x33,
    HarryHermionePortInTimeCutscene  = 0x34,
    HarryPatronusCutscene            = 0x35,
    LupinPotionCutscene              = 0x36,
    Credits                          = 0x37,
    Intro                            = 0x38,
    HarryArrivedAtHogwartsCutscene   = 0x39,
    UnusedChristmasArrivedCutscene   = 0x3A,
    SiriusBlackCutscene              = 0x3B,
    PeterPettigrewCutscene           = 0x3C,
    RonSleepingCutscene              = 0x3D,
    TimeTurnerPermissionCutscene     = 0x3E,
    HippogriffTookToAirCutscene      = 0x3F,
    GameCompletedReplayCutscene      = 0x40,
    GameCubeLink                     = 0x41,
    OwlNameSelect                    = 0x42,
    QuantitySelectScreen             = 0x43,
    HelpTopicScreen                  = 0x44,
    HippogriffFliesIntoAirCutscene   = 0x45,
    CardComboDescription             = 0x46,
    ConfirmTradeScreen               = 0x47,
} GameMode;

extern void PushGameMode_3(GameMode mode, s32 arg1, s32 arg2, s32 arg3);
extern void PushGameMode_2(GameMode mode, s32 arg1, s32 arg2);
extern void PushGameMode(GameMode mode);
extern u32 GetPendingGameMode_candidate(void);

// The three arg words (+4/+8/+0xC) are generic per-mode parameters, set by
// PushGameMode_2/PushGameMode_3 and read by the mode's own init -- e.g.
// battle reads arg1 as the overworld slot. Accessed through one shared
// base register in the real code, hence one struct here rather than
// standalone globals.
typedef struct {
    u32 dwCurrentGameMode;         // 0x00 (0x03003EF4)
    u32 dwCurrentGameModeArg1;     // 0x04
    u32 dwCurrentGameModeArg2;     // 0x08
    u32 dwCurrentGameModeArg3;     // 0x0C
    u32 dwModeState;               // 0x10; per-mode state machine, cleared on push
    u32 dwModeScratchA;            // 0x14; generic per-mode scratch word, e.g. a
                                   // confirm/cancel flag in OwlNameSelect, a
                                   // just-cancelled marker in CardTrade
    u32 dwModeTimer;               // 0x18; per-mode countdown, cleared on push
    u32 dwModeSubState;            // 0x1C; second per-mode state word
    u32 dwModeScratchB;            // 0x20; generic per-mode scratch word, same
                                   // reuse pattern as dwModeScratchA
} GameModeStackContext;
extern GameModeStackContext g_GameModeStackContext;  // 0x03003EF4

// Mirrors g_GameModeStackContext's layout for the not-yet-applied mode --
// PushGameMode/PushGameMode_2/PushGameMode_3 stage here, TickGameModeStack
// shifts it into g_GameModeStackContext on pop. Only the two fields ExitBattle
// touches are named; see docs/memory-map/game_modes.md for the rest.
extern GameModeStackContext g_dwPendingGameMode;  // 0x03003F18

// The third of three identical 0x24-byte blocks (current/pending/previous)
// TickGameModeStack shifts through on every mode transition: the mode
// g_GameModeStackContext held just before this frame's pop.
extern GameModeStackContext g_PrevGameModeStackContext;  // 0x03003F3C

extern void InitGameModeStack(void);
extern void TickGameModeStack(void);

// One dispatch-table entry per GameMode; see g_pGameModeDispatchTable below.
typedef struct {
    void (*pInitFn)(void);
    void (*pUpdateFn)(void);
    void (*pDestroyFn)(void);
} GameModeDispatchEntry;

// 72 entries (GameMode 0-0x47), see docs/memory-map/game_modes.md.
extern const GameModeDispatchEntry g_pGameModeDispatchTable[72];  // src/gamemode/game_mode_dispatch_table.c

// Runs the current mode's pInitFn/pUpdateFn/pDestroyFn slot out of
// g_pGameModeDispatchTable. DispatchGameModeInit additionally calls
// ResetKeyInput first; DispatchGameModeDestroy additionally checks
// g_dwGameModeFlags bit 0x1 before dispatching.
extern void DispatchGameModeInit(void);
extern void DispatchGameModeUpdate(void);
extern void DispatchGameModeDestroy(void);

// g_dwCurrentGameMode != g_dwPendingGameMode.dwCurrentGameMode, i.e. whether
// TickGameModeStack has a mode change to apply this frame.
extern s32 IsGameModeTransitionPending(void);

// See ram_symbols.us.inc: 0x03003B44, a broad game-mode-state flags word
// touched by dozens of functions across overworld/room/cutscene transitions.
extern u32 g_dwGameModeFlags;

typedef enum {
    LinkSessionActive = 0x20,
} GameModeFlags;

// u32: incremented once per TickGameModeStack call, before mode dispatch.
// Also used by UpdateObjectSpriteFrame as a per-tick generation stamp for
// its shared VRAM tile allocation cache.
extern u32 g_dwTickCount;

// Ticks active objects, particle emitters, and several other per-frame
// subsystems; called once/frame from TickGameModeStack after
// DispatchGameModeUpdate. See docs/memory-map/frame_systems.md.
extern void TickFrameSystems(void);

// Pumps the link-cable comm packet when a link session is active
// (g_dwGameModeFlags bit 0x20); see docs/memory-map/link.md.
extern void TickLinkCommIfActive_candidate(void);
