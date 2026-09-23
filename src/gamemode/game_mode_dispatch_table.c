#include "types.h"
#include "game_modes.h"

extern void ExitLoadingScreen();
extern void ExitCardComboDescription();
extern void ExitCardTrade();
extern void ExitClockSkipCutscene();
extern void ExitConnectivity();
extern void ExitCoolTrainCutscene();
extern void ExitConfirmTradeScreen();
extern void ExitDebugCharacterSelectMenu();
extern void ExitDebugCollectorCardsMenu();
extern void ExitDebugLevelAndQuestSelectMenu();
extern void ExitDebugMapSelectMenu();
extern void ExitDebugMenuMain();
extern void ExitDebugPortraitsMenu();
extern void ExitDebugSoundTestMenu();
extern void ExitDialogue();
extern void ExitDivinationTeaMinigame();
extern void ExitFolioBruti();
extern void ExitFolioUniversitas();
extern void ExitFolioCardDetailScreen();
extern void ExitFolios();
extern void ExitFredAndGeorgesShop();
extern void ExitGameSave();
extern void ExitHarryHermionePortInTimeCutscene();
extern void ExitHarryPatronusCutscene();
extern void ExitHarryVsDementorsMinigame();
extern void ExitHelpScreen();
extern void ExitHighScoreNameEntry();
extern void ExitHippogriffFliesIntoAirCutscene();
extern void ExitHippogriffGlideMinigame();
extern void ExitHogwartsUpNightCutscene();
extern void ExitInGameMenu();
extern void ExitItemUseScreen();
extern void ExitItemsItemSelect();
extern void ExitItemsSectionSelect();
extern void ExitLanguageSelect();
extern void ExitGameCubeLink();
extern void ExitLinearCutscene();
extern void ExitLupinPotionCutscene();
extern void ExitMainMenuScreen();
extern void ExitMinigameMenu();
extern void ExitNewGameMenu();
extern void ExitOptions();
extern void ExitOverworldScreen();
extern void ExitOwlNameSelect();
extern void ExitPurpleScreenReturnToMenu();
extern void ExitQuantitySelectScreen();
extern void ExitRiddikulusMinigame();
extern void ExitStartup();
extern void ExitStatusEquipCharacterSelect();
extern void ExitStatusEquipSlotSelect();
extern void ExitStatusEquipItemSelect();
extern void ExitUnusedHogwartsMapScreen();
extern void ExitUnusedServePumpkinJuiceMinigame();
extern void ExitWizardCrackerPopItDifficultySelect();
extern void ExitTopicScreen();
extern void ExitWizardCrackerPopItMinigame();
extern void ExitBattle();
extern void ExitVictoryScreen();
extern void HandleConnectivityMenuTick();
extern void HandleFolioCardDetailScreenTick();
extern void HandleGameModeNoneNoOp();
extern void HandleHighScoreDifficultyMenuTick();
extern void HandleMinigameSelectMenuConfirm();
extern void HandleOwlCareKitScreenExit();
extern void HandleOwlCareKitScreenTick();
extern void HandleSaveLoadContinuation();
extern void InitializeBattle();
extern void InitializeLoadingScreen();
extern void InitializeCardComboDescription();
extern void InitializeCardTrade();
extern void InitializeClockSkipCutscene();
extern void InitializeConnectivityMenu();
extern void InitializeCoolTrainCutscene();
extern void InitializeCredits();
extern void InitializeConfirmTradeScreen();
extern void InitializeDebugCharacterSelectMenu();
extern void InitializeDebugCollectorCardsMenu();
extern void InitializeDebugLevelAndQuestSelectMenu();
extern void InitializeDebugMapSelectMenu();
extern void InitializeDebugMenuMain();
extern void InitializeDebugPortraitsMenu();
extern void InitializeDebugSoundTestMenu();
extern void InitializeDialogue();
extern void InitializeDivinationTeaMinigame();
extern void InitializeFolioBruti();
extern void InitializeFolioCardDetailScreen();
extern void InitializeFolioUniversitas();
extern void InitializeFolios();
extern void InitializeFredAndGeorgesShop();
extern void InitializeGameSave();
extern void InitializeHarryHermionePortInTimeCutscene();
extern void InitializeHarryPatronusCutscene();
extern void InitializeHarryVsDementorsMinigame();
extern void InitializeHelp();
extern void InitializeHighScoreNameEntryScreen();
extern void InitializeHippogriffFliesIntoAirCutscene();
extern void InitializeHippogriffGlideMinigame();
extern void InitializeHogwartsUpNightCutscene();
extern void InitializeInGameMenu();
extern void InitializeInGameMenuFadeIn();
extern void InitializeItemUseScreen();
extern void InitializeItemsItemSelect();
extern void InitializeItemsSectionSelect();
extern void InitializeLanguageSelect();
extern void InitializeGameCubeLink();
extern void InitializeLinearCutscene();
extern void InitializeLoadGame();
extern void InitializeLupinPotionCutscene();
extern void InitializeMainMenu();
extern void InitializeMinigameMenu();
extern void InitializeNewGameMenu();
extern void InitializeOptions();
extern void InitializeOverworld();
extern void InitializeOwlCareKitScreen();
extern void InitializeOwlNameSelect();
extern void InitializePurpleScreenReturnToMenu();
extern void InitializeQuantitySelectScreen();
extern void InitializeRiddikulusMinigame();
extern void InitializeStartup();
extern void InitializeStatusEquipCharacterSelect();
extern void InitializeStatusEquipCharacterSelectLastCursor();
extern void InitializeStatusEquipSlotSelect();
extern void InitializeStatusEquipItemSelect();
extern void InitializeUnusedHogwartsMapScreen();
extern void InitializeUnusedServePumpkinJuiceMinigame();
extern void InitializeVictoryScreen();
extern void InitializeWizardCrackerPopItDifficultySelect();
extern void InitializeTopicScreen();
extern void InitializeWizardCrackerPopItMinigame();
extern void UpdateBattle();
extern void UpdateLoadingScreen();
extern void UpdateCardComboDescription();
extern void UpdateCardTrade();
extern void UpdateClockSkipCutscene();
extern void UpdateCoolTrainCutscene();
extern void UpdateCredits();
extern void UpdateConfirmTradeScreen();
extern void UpdateDebugCharacterSelectMenu();
extern void UpdateDebugCollectorCardsMenu();
extern void UpdateDebugLevelAndQuestSelectMenu();
extern void UpdateDebugMapSelectMenu();
extern void UpdateDebugMenuMain();
extern void UpdateDebugPortraitsMenu();
extern void UpdateDebugSoundTestMenu();
extern void UpdateDialogueBox();
extern void UpdateDivinationTeaMinigame();
extern void UpdateFolioBrutiGridCursor();
extern void UpdateFolioUniversitas();
extern void UpdateFolios();
extern void UpdateFredAndGeorgesShop();
extern void UpdateGameSave();
extern void UpdateHarryHermionePortInTimeCutscene();
extern void UpdateHarryPatronusCutscene();
extern void UpdateHarryVsDementorsMinigame();
extern void UpdateHelp();
extern void UpdateHighScoreNameEntry();
extern void UpdateHippogriffFliesIntoAirCutscene();
extern void UpdateHippogriffGlideMinigame();
extern void UpdateHogwartsUpNightCutscene();
extern void UpdateInGameMenu();
extern void UpdateItemUseScreen();
extern void UpdateItemsItemSelect();
extern void UpdateItemsSectionSelect();
extern void UpdateLanguageSelect();
extern void UpdateGameCubeLink();
extern void UpdateLinearCutscene();
extern void UpdateLoadGame();
extern void UpdateLupinPotionCutscene();
extern void UpdateMainMenu();
extern void UpdateNewGameMenu();
extern void UpdateOptions();
extern void UpdateOverworld();
extern void UpdateOwlNameSelect();
extern void UpdatePurpleScreenReturnToMenu();
extern void UpdateQuantitySelectScreen();
extern void UpdateRiddikulusMinigame();
extern void UpdateStartup();
extern void UpdateStatusEquipCharacterSelect();
extern void UpdateStatusEquipSlotSelect();
extern void UpdateStatusEquipItemSelect();
extern void UpdateUnusedHogwartsMapScreen();
extern void UpdateUnusedServePumpkinJuiceMinigame();
extern void UpdateVictoryScreen();
extern void UpdateTopicScreen();
extern void UpdateWizardCrackerPopItMinigame();

// Indexed by GameMode (0 unused/reserved). See docs/memory-map/game_modes.md.
const GameModeDispatchEntry g_pGameModeDispatchTable[72] = {
    { HandleGameModeNoneNoOp, HandleGameModeNoneNoOp, HandleGameModeNoneNoOp },
    { InitializeStartup, UpdateStartup, ExitStartup },
    { InitializeLanguageSelect, UpdateLanguageSelect, ExitLanguageSelect },
    { InitializeMainMenu, UpdateMainMenu, ExitMainMenuScreen },
    { InitializeLoadGame, UpdateLoadGame, HandleSaveLoadContinuation },
    { InitializeOptions, UpdateOptions, ExitOptions },
    { InitializeMinigameMenu, HandleMinigameSelectMenuConfirm, ExitMinigameMenu },
    { InitializeNewGameMenu, UpdateNewGameMenu, ExitNewGameMenu },
    { InitializeOverworld, UpdateOverworld, ExitOverworldScreen },
    { InitializeBattle, UpdateBattle, ExitBattle },
    { InitializeInGameMenu, UpdateInGameMenu, ExitInGameMenu },
    { InitializeInGameMenuFadeIn, UpdateInGameMenu, ExitInGameMenu },
    { InitializeStatusEquipCharacterSelect, UpdateStatusEquipCharacterSelect, ExitStatusEquipCharacterSelect },
    { InitializeStatusEquipCharacterSelectLastCursor, UpdateStatusEquipCharacterSelect, ExitStatusEquipCharacterSelect },
    { InitializeStatusEquipSlotSelect, UpdateStatusEquipSlotSelect, ExitStatusEquipSlotSelect },
    { InitializeStatusEquipItemSelect, UpdateStatusEquipItemSelect, ExitStatusEquipItemSelect },
    { InitializeItemsSectionSelect, UpdateItemsSectionSelect, ExitItemsSectionSelect },
    { InitializeItemsItemSelect, UpdateItemsItemSelect, ExitItemsItemSelect },
    { InitializeItemUseScreen, UpdateItemUseScreen, ExitItemUseScreen },
    { InitializeFolios, UpdateFolios, ExitFolios },
    { InitializeGameSave, UpdateGameSave, ExitGameSave },
    { InitializeCardTrade, UpdateCardTrade, ExitCardTrade },
    { InitializeConnectivityMenu, HandleConnectivityMenuTick, ExitConnectivity },
    { InitializeHelp, UpdateHelp, ExitHelpScreen },
    { InitializeDialogue, UpdateDialogueBox, ExitDialogue },
    { InitializeDebugMenuMain, UpdateDebugMenuMain, ExitDebugMenuMain },
    { InitializeLoadingScreen, UpdateLoadingScreen, ExitLoadingScreen },
    { InitializeWizardCrackerPopItMinigame, UpdateWizardCrackerPopItMinigame, ExitWizardCrackerPopItMinigame },
    { InitializeDivinationTeaMinigame, UpdateDivinationTeaMinigame, ExitDivinationTeaMinigame },
    { InitializeHighScoreNameEntryScreen, UpdateHighScoreNameEntry, ExitHighScoreNameEntry },
    { InitializeWizardCrackerPopItDifficultySelect, HandleHighScoreDifficultyMenuTick, ExitWizardCrackerPopItDifficultySelect },
    { InitializeDebugMapSelectMenu, UpdateDebugMapSelectMenu, ExitDebugMapSelectMenu },
    { InitializeDebugLevelAndQuestSelectMenu, UpdateDebugLevelAndQuestSelectMenu, ExitDebugLevelAndQuestSelectMenu },
    { InitializeDebugSoundTestMenu, UpdateDebugSoundTestMenu, ExitDebugSoundTestMenu },
    { InitializeDebugCollectorCardsMenu, UpdateDebugCollectorCardsMenu, ExitDebugCollectorCardsMenu },
    { InitializeDebugPortraitsMenu, UpdateDebugPortraitsMenu, ExitDebugPortraitsMenu },
    { InitializeUnusedServePumpkinJuiceMinigame, UpdateUnusedServePumpkinJuiceMinigame, ExitUnusedServePumpkinJuiceMinigame },
    { InitializeUnusedHogwartsMapScreen, UpdateUnusedHogwartsMapScreen, ExitUnusedHogwartsMapScreen },
    { InitializeFolioUniversitas, UpdateFolioUniversitas, ExitFolioUniversitas },
    { InitializeCoolTrainCutscene, UpdateCoolTrainCutscene, ExitCoolTrainCutscene },
    { InitializeFolioCardDetailScreen, HandleFolioCardDetailScreenTick, ExitFolioCardDetailScreen },
    { InitializeOwlCareKitScreen, HandleOwlCareKitScreenTick, HandleOwlCareKitScreenExit },
    { InitializeDebugCharacterSelectMenu, UpdateDebugCharacterSelectMenu, ExitDebugCharacterSelectMenu },
    { InitializeHippogriffGlideMinigame, UpdateHippogriffGlideMinigame, ExitHippogriffGlideMinigame },
    { InitializeVictoryScreen, UpdateVictoryScreen, ExitVictoryScreen },
    { InitializeFolioBruti, UpdateFolioBrutiGridCursor, ExitFolioBruti },
    { InitializeFredAndGeorgesShop, UpdateFredAndGeorgesShop, ExitFredAndGeorgesShop },
    { InitializeRiddikulusMinigame, UpdateRiddikulusMinigame, ExitRiddikulusMinigame },
    { InitializeClockSkipCutscene, UpdateClockSkipCutscene, ExitClockSkipCutscene },
    { InitializeHogwartsUpNightCutscene, UpdateHogwartsUpNightCutscene, ExitHogwartsUpNightCutscene },
    { InitializePurpleScreenReturnToMenu, UpdatePurpleScreenReturnToMenu, ExitPurpleScreenReturnToMenu },
    { InitializeHarryVsDementorsMinigame, UpdateHarryVsDementorsMinigame, ExitHarryVsDementorsMinigame },
    { InitializeHarryHermionePortInTimeCutscene, UpdateHarryHermionePortInTimeCutscene, ExitHarryHermionePortInTimeCutscene },
    { InitializeHarryPatronusCutscene, UpdateHarryPatronusCutscene, ExitHarryPatronusCutscene },
    { InitializeLupinPotionCutscene, UpdateLupinPotionCutscene, ExitLupinPotionCutscene },
    { InitializeCredits, UpdateCredits, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeLinearCutscene, UpdateLinearCutscene, ExitLinearCutscene },
    { InitializeGameCubeLink, UpdateGameCubeLink, ExitGameCubeLink },
    { InitializeOwlNameSelect, UpdateOwlNameSelect, ExitOwlNameSelect },
    { InitializeQuantitySelectScreen, UpdateQuantitySelectScreen, ExitQuantitySelectScreen },
    { InitializeTopicScreen, UpdateTopicScreen, ExitTopicScreen },
    { InitializeHippogriffFliesIntoAirCutscene, UpdateHippogriffFliesIntoAirCutscene, ExitHippogriffFliesIntoAirCutscene },
    { InitializeCardComboDescription, UpdateCardComboDescription, ExitCardComboDescription },
    { InitializeConfirmTradeScreen, UpdateConfirmTradeScreen, ExitConfirmTradeScreen },
};
