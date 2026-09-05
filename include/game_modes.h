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
    BlackScreen                      = 0x1A,
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
    LastMenuScreen                   = 0x41,
    OwlNameSelect                    = 0x42,
    QuantitySelectScreen             = 0x43,
    HelpTopicScreen                  = 0x44,
    HippogriffFliesIntoAirCutscene   = 0x45,
    CardComboDescription             = 0x46,
    CreditsAgain                     = 0x47,
} GameMode;

extern void PushGameMode_2(GameMode mode, s32 arg1, s32 arg2);
extern void PushGameMode(GameMode mode);

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

extern void InitGameModeStack(void);
extern void TickGameModeStack_candidate(void);

// See ram_symbols.us.inc: 0x03003B44, a broad game-mode-state flags word
// touched by dozens of functions across overworld/room/cutscene transitions.
extern u32 g_dwGameModeFlags;
