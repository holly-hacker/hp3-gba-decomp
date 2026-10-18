#include "modes.h"
#include "boggart_minigame.h"
#include "buckbeak_minigame.h"
#include "challenge_unused.h"
#include "cheat.h"
#include "cheat_level_and_quest.h"
#include "cheat_map.h"
#include "cheat_party.h"
#include "cheat_portraits.h"
#include "cheat_sound_test.h"
#include "cheat_wizard_cards.h"
#include "choose_party_member.h"
#include "combat.h"
#include "combat_result.h"
#include "combo_info.h"
#include "credits_cutscene.h"
#include "dementor_minigame.h"
#include "dev_logos.h"
#include "dialog.h"
#include "ending_cutscene.h"
#include "hedwig_minigame.h"
#include "initials.h"
#include "instructions_screen.h"
#include "landmarks.h"
#include "language_select.h"
#include "lupin_potion_cutscene.h"
#include "map.h"
#include "minigame_difficulty_select.h"
#include "minigame_menu.h"
#include "owl_name_select.h"
#include "patronus_cutscene.h"
#include "pause_menu.h"
#include "pop_it_minigame.h"
#include "pouring_minigame.h"
#include "pscreen_character.h"
#include "pscreen_connectivity.h"
#include "pscreen_equip.h"
#include "pscreen_folio.h"
#include "pscreen_folio_bruti.h"
#include "pscreen_folio_universitas.h"
#include "pscreen_gamecube.h"
#include "pscreen_information.h"
#include "pscreen_item_count.h"
#include "pscreen_items.h"
#include "pscreen_save.h"
#include "pscreen_status_equip.h"
#include "pscreen_trade.h"
#include "pscreen_wizard_cards.h"
#include "store.h"
#include "tea_leaves_minigame.h"
#include "time_skip_cutscene.h"
#include "timeturner_cutscene.h"
#include "title.h"
#include "title_load.h"
#include "title_new.h"
#include "title_options.h"
#include "train_cutscene.h"

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
    { InitializeDialog, UpdateDialogBox, ExitDialog },
    { InitializeCheat, UpdateCheat, ExitCheat },
    { InitializeChooseCharacter, UpdateChooseCharacter, ExitChooseCharacter },
    { InitializeWizardCrackerPopItMinigame, UpdateWizardCrackerPopItMinigame, ExitWizardCrackerPopItMinigame },
    { InitializeDivinationTeaMinigame, UpdateDivinationTeaMinigame, ExitDivinationTeaMinigame },
    { InitializeHighScoreNameEntryScreen, UpdateHighScoreNameEntry, ExitHighScoreNameEntry },
    { InitializeWizardCrackerPopItDifficultySelect, HandleHighScoreDifficultyMenuTick, ExitWizardCrackerPopItDifficultySelect },
    { InitializeCheatMap, UpdateCheatMap, ExitCheatMap },
    { InitializeCheatLevelAndQuest, UpdateCheatLevelAndQuest, ExitCheatLevelAndQuest },
    { InitializeCheatSoundTest, UpdateCheatSoundTest, ExitCheatSoundTest },
    { InitializeCheatWizardCards, UpdateCheatWizardCards, ExitCheatWizardCards },
    { InitializeCheatPortraits, UpdateCheatPortraits, ExitCheatPortraits },
    { InitializeUnusedServePumpkinJuiceMinigame, UpdateUnusedServePumpkinJuiceMinigame, ExitUnusedServePumpkinJuiceMinigame },
    { InitializeUnusedHogwartsMapScreen, UpdateUnusedHogwartsMapScreen, ExitUnusedHogwartsMapScreen },
    { InitializeFolioUniversitas, UpdateFolioUniversitas, ExitFolioUniversitas },
    { InitializeCoolTrainCutscene, UpdateCoolTrainCutscene, ExitCoolTrainCutscene },
    { InitializeFolioCardDetailScreen, HandleFolioCardDetailScreenTick, ExitFolioCardDetailScreen },
    { InitializeOwlCareKitScreen, HandleOwlCareKitScreenTick, HandleOwlCareKitScreenExit },
    { InitializeCheatParty, UpdateCheatParty, ExitCheatParty },
    { InitializeBuckbeakMinigame, UpdateBuckbeakMinigame, ExitBuckbeakMinigame },
    { InitializeCombatResult, UpdateCombatResult, ExitCombatResult },
    { InitializeFolioBruti, UpdateFolioBrutiGridCursor, ExitFolioBruti },
    { InitializeFredAndGeorgesShop, UpdateFredAndGeorgesShop, ExitFredAndGeorgesShop },
    { InitializeBoggartMinigame, UpdateBoggartMinigame, ExitBoggartMinigame },
    { InitializeClockSkipCutscene, UpdateClockSkipCutscene, ExitClockSkipCutscene },
    { InitializeHogwartsUpNightCutscene, UpdateHogwartsUpNightCutscene, ExitHogwartsUpNightCutscene },
    { InitializeUnusedMinigame, UpdateUnusedMinigame, ExitUnusedMinigame },
    { InitializeDementorMinigame, UpdateDementorMinigame, ExitDementorMinigame },
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
