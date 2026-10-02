# Game Modes

The game uses a global "Game Mode" variable to indicate in which type of screen you are. Screens include the main menu,
the startup sequence, walking around on the overworld, watching a cutscene, navigating a debug menu, etc. These game
modes can take up to 3 arguments and have 5 mode-specific variables.

Each game mode has an `init`, `update` and `destroy` function. These live in a table at `0x08065CBC`/`0x08065C48`
(US/JP). The `update` function is called on each game frame (at ~30fps). When switching between game modes, first the
`destroy` function of the current game mode is called, then the `init` function of the new game mode.

The game mode data is defined like so:

```c
typedef struct {
    u32 dwCurrentGameMode;     // 0x00
    u32 dwCurrentGameModeArg1; // 0x04
    u32 dwCurrentGameModeArg2; // 0x08
    u32 dwCurrentGameModeArg3; // 0x0C
    u32 dwModeState;           // 0x10
    u32 dwModeScratchA;        // 0x14
    u32 dwModeTimer;           // 0x18
    u32 dwModeSubState;        // 0x1C
    u32 dwModeScratchB;        // 0x20
} GameModeStackContext;
```

This struct lives at 3 positions (US/JP):

- `0x03003EF4`/`0x03003F54`: Current game mode
- `0x03003F18`/`0x03003F78`: Next/pending game mode
- `0x03003F3C`/`0x03003F9C`: Previous game mode

To initiate a game mode transition, overwrite `dwCurrentGameMode` of the pending game mode object with the new game mode
id, ORed with 0x80. For example, to enter the debug menu, set it to `0x99`. For a proper transition, also fill in the
arguments and zero out `dwModeState`, `dwModeTimer` and any unused arguments.

## List of modes

### `None` (0x00)

This game mode contains no code and will simply hang, until a new game mode is requested externally. This game mode does
not get used in-game.

### `Startup` (0x01)

### `LanguageSelect` (0x02)

### `MainMenu` (0x03)

### `LoadGame` (0x04)

### `Options` (0x05)

### `MinigameMenu` (0x06)

### `NewGameMenu` (0x07)

### `Overworld` (0x08)

Arguments: `(?, roomId, ?)`

### `Battle` (0x09)

Arguments:

- `(roomId, variantId, kindId)`: Standard/random encounter, indexes into random encounter table as
  `table[room][kind][variant]`
- `(encounterId, unused, 0xFF)`: Scripted encounter

### `InGameMenu` (0x0A)

### `InGameMenuFadeIn` (0x0B)

### `StatusEquipCharacterSelect` (0x0C)

### `StatusEquipCharacterSelectLastCursor` (0x0D)

### `StatusEquipSlotSelect` (0x0E)

### `StatusEquipItemSelect` (0x0F)

### `ItemsSectionSelect` (0x10)

### `ItemsItemSelect` (0x11)

### `ItemUseScreen` (0x12)

### `Folios` (0x13)

### `GameSave` (0x14)

### `CardTrade` (0x15)

### `Connectivity` (0x16)

### `Help` (0x17)

### `Dialogue` (0x18)

### `DebugMenuMain` (0x19)

### `LoadingScreen` (0x1A)

### `WizardCrackerPopItMinigame` (0x1B)

### `DivinationTeaMinigame` (0x1C)

### `HighScoreNameEntryUnused` (0x1D)

### `MinigameDifficultySelect` (0x1E)

### `DebugMenuMapSelect` (0x1F)

### `DebugMenuLevelAndQuestSelect` (0x20)

### `DebugMenuSoundTest` (0x21)

### `DebugMenuCollectorCards` (0x22)

### `DebugMenuPortraits` (0x23)

### `UnusedServePumpkinJuiceMinigame` (0x24)

### `UnusedHogwartsMapScreen` (0x25)

### `FolioUniversitas` (0x26)

### `CoolTrainCutscene` (0x27)

### `FolioUniversitasCardDetails` (0x28)

### `OwlCareMinigame` (0x29)

### `DebugMenuCharacterSelect` (0x2A)

### `HippogriffGlideMinigame` (0x2B)

### `VictoryScreen` (0x2C)

### `FolioBruti` (0x2D)

### `FredAndGeorgesShop` (0x2E)

### `RiddikulusMinigame` (0x2F)

### `ClockSkipCutscene` (0x30)

### `HogwartsUpNightCutscene` (0x31)

### `PurpleScreenReturnToMenu` (0x32)

### `HarryVsDementorsMinigame` (0x33)

### `HarryHermionePortInTimeCutscene` (0x34)

### `HarryPatronusCutscene` (0x35)

### `LupinPotionCutscene` (0x36)

### `Credits` (0x37)

### `Intro` (0x38)

### `HarryArrivedAtHogwartsCutscene` (0x39)

### `UnusedChristmasArrivedCutscene` (0x3A)

### `SiriusBlackCutscene` (0x3B)

### `PeterPettigrewCutscene` (0x3C)

### `RonSleepingCutscene` (0x3D)

### `TimeTurnerPermissionCutscene` (0x3E)

### `HippogriffTookToAirCutscene` (0x3F)

### `GameCompletedReplayCutscene` (0x40)

### `GameCubeLink` (0x41)

### `OwlNameSelect` (0x42)

### `QuantitySelectScreen` (0x43)

### `HelpTopicScreen` (0x44)

### `HippogriffFliesIntoAirCutscene` (0x45)

### `CardComboDescription` (0x46)

### `ConfirmTradeScreen` (0x47)
