#include "types.h"

typedef struct {
    void *pInitFn;
    void *pUpdateFn;
    void *pDestroyFn;
} GameModeDispatchEntry;

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
extern void ExitStatusEquipHarryScreen();
extern void ExitStatusEquipHarryItemSelect();
extern void ExitUnusedHogwartsMapScreen();
extern void ExitUnusedServePumpkinJuiceMinigame();
extern void ExitWizardCrackerPopItDifficultySelect();
extern void ExitTopicScreen();
extern void ExitWizardCrackerPopItMinigame();
extern void ExitBattle();
extern void ExitVictoryScreen();
extern void HandleConnectivityMenuTick();
extern void HandleDebugTestMenuSelect();
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
extern void InitializeStatusEquipCharacterSelectC();
extern void InitializeStatusEquipCharacterSelectD();
extern void InitializeStatusEquipHarry();
extern void InitializeStatusEquipHarryItemSelect();
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
extern void UpdateStatusEquipHarry();
extern void UpdateStatusEquipHarryItemSelect();
extern void UpdateUnusedHogwartsMapScreen();
extern void UpdateUnusedServePumpkinJuiceMinigame();
extern void UpdateVictoryScreen();
extern void UpdateTopicScreen();
extern void UpdateWizardCrackerPopItMinigame();

// Indexed by GameMode (0 unused/reserved). See docs/memory-map/game_modes.md.
const GameModeDispatchEntry g_pGameModeDispatchTable[72] = {
    { (void *)HandleGameModeNoneNoOp, (void *)HandleGameModeNoneNoOp, (void *)HandleGameModeNoneNoOp },
    { (void *)InitializeStartup, (void *)UpdateStartup, (void *)ExitStartup },
    { (void *)InitializeLanguageSelect, (void *)UpdateLanguageSelect, (void *)ExitLanguageSelect },
    { (void *)InitializeMainMenu, (void *)UpdateMainMenu, (void *)ExitMainMenuScreen },
    { (void *)InitializeLoadGame, (void *)UpdateLoadGame, (void *)HandleSaveLoadContinuation },
    { (void *)InitializeOptions, (void *)UpdateOptions, (void *)ExitOptions },
    { (void *)InitializeMinigameMenu, (void *)HandleMinigameSelectMenuConfirm, (void *)ExitMinigameMenu },
    { (void *)InitializeNewGameMenu, (void *)UpdateNewGameMenu, (void *)ExitNewGameMenu },
    { (void *)InitializeOverworld, (void *)UpdateOverworld, (void *)ExitOverworldScreen },
    { (void *)InitializeBattle, (void *)UpdateBattle, (void *)ExitBattle },
    { (void *)InitializeInGameMenu, (void *)UpdateInGameMenu, (void *)ExitInGameMenu },
    { (void *)InitializeInGameMenuFadeIn, (void *)UpdateInGameMenu, (void *)ExitInGameMenu },
    { (void *)InitializeStatusEquipCharacterSelectC, (void *)UpdateStatusEquipCharacterSelect, (void *)ExitStatusEquipCharacterSelect },
    { (void *)InitializeStatusEquipCharacterSelectD, (void *)UpdateStatusEquipCharacterSelect, (void *)ExitStatusEquipCharacterSelect },
    { (void *)InitializeStatusEquipHarry, (void *)UpdateStatusEquipHarry, (void *)ExitStatusEquipHarryScreen },
    { (void *)InitializeStatusEquipHarryItemSelect, (void *)UpdateStatusEquipHarryItemSelect, (void *)ExitStatusEquipHarryItemSelect },
    { (void *)InitializeItemsSectionSelect, (void *)UpdateItemsSectionSelect, (void *)ExitItemsSectionSelect },
    { (void *)InitializeItemsItemSelect, (void *)UpdateItemsItemSelect, (void *)ExitItemsItemSelect },
    { (void *)InitializeItemUseScreen, (void *)UpdateItemUseScreen, (void *)ExitItemUseScreen },
    { (void *)InitializeFolios, (void *)UpdateFolios, (void *)ExitFolios },
    { (void *)InitializeGameSave, (void *)UpdateGameSave, (void *)ExitGameSave },
    { (void *)InitializeCardTrade, (void *)UpdateCardTrade, (void *)ExitCardTrade },
    { (void *)InitializeConnectivityMenu, (void *)HandleConnectivityMenuTick, (void *)ExitConnectivity },
    { (void *)InitializeHelp, (void *)UpdateHelp, (void *)ExitHelpScreen },
    { (void *)InitializeDialogue, (void *)UpdateDialogueBox, (void *)ExitDialogue },
    { (void *)InitializeDebugMenuMain, (void *)HandleDebugTestMenuSelect, (void *)ExitDebugMenuMain },
    { (void *)InitializeLoadingScreen, (void *)UpdateLoadingScreen, (void *)ExitLoadingScreen },
    { (void *)InitializeWizardCrackerPopItMinigame, (void *)UpdateWizardCrackerPopItMinigame, (void *)ExitWizardCrackerPopItMinigame },
    { (void *)InitializeDivinationTeaMinigame, (void *)UpdateDivinationTeaMinigame, (void *)ExitDivinationTeaMinigame },
    { (void *)InitializeHighScoreNameEntryScreen, (void *)UpdateHighScoreNameEntry, (void *)ExitHighScoreNameEntry },
    { (void *)InitializeWizardCrackerPopItDifficultySelect, (void *)HandleHighScoreDifficultyMenuTick, (void *)ExitWizardCrackerPopItDifficultySelect },
    { (void *)InitializeDebugMapSelectMenu, (void *)UpdateDebugMapSelectMenu, (void *)ExitDebugMapSelectMenu },
    { (void *)InitializeDebugLevelAndQuestSelectMenu, (void *)UpdateDebugLevelAndQuestSelectMenu, (void *)ExitDebugLevelAndQuestSelectMenu },
    { (void *)InitializeDebugSoundTestMenu, (void *)UpdateDebugSoundTestMenu, (void *)ExitDebugSoundTestMenu },
    { (void *)InitializeDebugCollectorCardsMenu, (void *)UpdateDebugCollectorCardsMenu, (void *)ExitDebugCollectorCardsMenu },
    { (void *)InitializeDebugPortraitsMenu, (void *)UpdateDebugPortraitsMenu, (void *)ExitDebugPortraitsMenu },
    { (void *)InitializeUnusedServePumpkinJuiceMinigame, (void *)UpdateUnusedServePumpkinJuiceMinigame, (void *)ExitUnusedServePumpkinJuiceMinigame },
    { (void *)InitializeUnusedHogwartsMapScreen, (void *)UpdateUnusedHogwartsMapScreen, (void *)ExitUnusedHogwartsMapScreen },
    { (void *)InitializeFolioUniversitas, (void *)UpdateFolioUniversitas, (void *)ExitFolioUniversitas },
    { (void *)InitializeCoolTrainCutscene, (void *)UpdateCoolTrainCutscene, (void *)ExitCoolTrainCutscene },
    { (void *)InitializeFolioCardDetailScreen, (void *)HandleFolioCardDetailScreenTick, (void *)ExitFolioCardDetailScreen },
    { (void *)InitializeOwlCareKitScreen, (void *)HandleOwlCareKitScreenTick, (void *)HandleOwlCareKitScreenExit },
    { (void *)InitializeDebugCharacterSelectMenu, (void *)UpdateDebugCharacterSelectMenu, (void *)ExitDebugCharacterSelectMenu },
    { (void *)InitializeHippogriffGlideMinigame, (void *)UpdateHippogriffGlideMinigame, (void *)ExitHippogriffGlideMinigame },
    { (void *)InitializeVictoryScreen, (void *)UpdateVictoryScreen, (void *)ExitVictoryScreen },
    { (void *)InitializeFolioBruti, (void *)UpdateFolioBrutiGridCursor, (void *)ExitFolioBruti },
    { (void *)InitializeFredAndGeorgesShop, (void *)UpdateFredAndGeorgesShop, (void *)ExitFredAndGeorgesShop },
    { (void *)InitializeRiddikulusMinigame, (void *)UpdateRiddikulusMinigame, (void *)ExitRiddikulusMinigame },
    { (void *)InitializeClockSkipCutscene, (void *)UpdateClockSkipCutscene, (void *)ExitClockSkipCutscene },
    { (void *)InitializeHogwartsUpNightCutscene, (void *)UpdateHogwartsUpNightCutscene, (void *)ExitHogwartsUpNightCutscene },
    { (void *)InitializePurpleScreenReturnToMenu, (void *)UpdatePurpleScreenReturnToMenu, (void *)ExitPurpleScreenReturnToMenu },
    { (void *)InitializeHarryVsDementorsMinigame, (void *)UpdateHarryVsDementorsMinigame, (void *)ExitHarryVsDementorsMinigame },
    { (void *)InitializeHarryHermionePortInTimeCutscene, (void *)UpdateHarryHermionePortInTimeCutscene, (void *)ExitHarryHermionePortInTimeCutscene },
    { (void *)InitializeHarryPatronusCutscene, (void *)UpdateHarryPatronusCutscene, (void *)ExitHarryPatronusCutscene },
    { (void *)InitializeLupinPotionCutscene, (void *)UpdateLupinPotionCutscene, (void *)ExitLupinPotionCutscene },
    { (void *)InitializeCredits, (void *)UpdateCredits, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeLinearCutscene, (void *)UpdateLinearCutscene, (void *)ExitLinearCutscene },
    { (void *)InitializeGameCubeLink, (void *)UpdateGameCubeLink, (void *)ExitGameCubeLink },
    { (void *)InitializeOwlNameSelect, (void *)UpdateOwlNameSelect, (void *)ExitOwlNameSelect },
    { (void *)InitializeQuantitySelectScreen, (void *)UpdateQuantitySelectScreen, (void *)ExitQuantitySelectScreen },
    { (void *)InitializeTopicScreen, (void *)UpdateTopicScreen, (void *)ExitTopicScreen },
    { (void *)InitializeHippogriffFliesIntoAirCutscene, (void *)UpdateHippogriffFliesIntoAirCutscene, (void *)ExitHippogriffFliesIntoAirCutscene },
    { (void *)InitializeCardComboDescription, (void *)UpdateCardComboDescription, (void *)ExitCardComboDescription },
    { (void *)InitializeConfirmTradeScreen, (void *)UpdateConfirmTradeScreen, (void *)ExitConfirmTradeScreen },
};
