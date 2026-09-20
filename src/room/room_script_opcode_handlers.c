#include "types.h"
#include "room_script.h"
#include "room_script_opcodes.h"

// Room-script opcode -> handler table; see docs/formats/room_scripts.md.
// Opcode 0 ends a chain and has no handler.

const RoomScriptOpcodeHandler g_apRoomScriptOpcodeHandlers[93] = {
    0,  // 0: chain terminator
    RoomScriptOpDespawnTileObject,  // 1
    RoomScriptOp2,  // 2
    RoomScriptOpSetTileObjectFlagBit,  // 3
    RoomScriptOpClearTileObjectFlagBit,  // 4
    RoomScriptOpShowRoomDialog,  // 5
    RoomScriptOpPauseMusic,  // 6
    RoomScriptOpResumeMusic,  // 7
    RoomScriptOpPlayMusicModuleAndFlagIfChain1,  // 8
    RoomScriptOpPlayRoomSoundEffect,  // 9
    RoomScriptOpPlaySoundById,  // 10
    RoomScriptOpSetRoomMusicVolume,  // 11
    RoomScriptOpSetSoundEffectVolume,  // 12
    RoomScriptOpSetCameraPanSpeedOrRunRowChain,  // 13
    RoomScriptOpSetStoryStage,  // 14
    RoomScriptOpSetTileObjectAnimState,  // 15
    RoomScriptOpQueueTileObjectMove,  // 16
    RoomScriptOpReturnToOverworld,  // 17
    RoomScriptOpSetAllQueuedMoveParams,  // 18
    RoomScriptOpClearAllQueuedMoves,  // 19
    RoomScriptOpSetTileObjectPosition,  // 20
    RoomScriptOpPlayCutscene,  // 21
    RoomScriptOpCloseRoomDialog,  // 22
    RoomScriptOpSetTileObjectShadow,  // 23
    RoomScriptOpStartObjectAnimSequence,  // 24
    RoomScriptOpStartTileObjectScript,  // 25
    RoomScriptOpPlayTileObjectAnimation,  // 26
    RoomScriptOpOpenMainMenu,  // 27
    RoomScriptOpArmChainYield,  // 28
    RoomScriptOpGotoIfQuestStateCompare,  // 29
    RoomScriptOpGotoIfQuestStatePairCompare,  // 30
    RoomScriptOpSetQuestState,  // 31
    RoomScriptOpCopyQuestState,  // 32
    RoomScriptOpCancelObjectAnimSequence,  // 33
    RoomScriptOpSetTileObjectAnimStateWithSpeed,  // 34
    RoomScriptOpPatchRoomBackgroundTile,  // 35
    RoomScriptOpShowLoadingScreenTransition,  // 36
    RoomScriptOpPlayScreenTransitionOut,  // 37
    RoomScriptOpPlayScreenTransitionIn,  // 38
    RoomScriptOpRecruitPartyFollower,  // 39
    RoomScriptOpRemovePartyFollower,  // 40
    RoomScriptOpSpawnPartyFollowerAtTile,  // 41
    RoomScriptOp42,  // 42
    RoomScriptOpStartBattle,  // 43
    RoomScriptOpSetTileObjectAnimStateValue,  // 44
    RoomScriptOpGrantRoomReward,  // 45
    RoomScriptOpSetBackgroundBlendLayers,  // 46
    RoomScriptOpShowBackgroundLayer,  // 47
    RoomScriptOpHideBackgroundLayer,  // 48
    RoomScriptOpSetBackgroundPriority,  // 49
    RoomScriptOp50,  // 50
    RoomScriptOpPlaySpecialSceneEffect,  // 51
    RoomScriptOpSetCameraPanSpeedOrRunRowChainAlt,  // 52
    RoomScriptOpSetTileObjectAndLinkedVisible,  // 53
    RoomScriptOpGotoIfStoryStageCompare,  // 54
    RoomScriptOpSetRandomQuestState,  // 55
    RoomScriptOpNoOp,  // 56
    RoomScriptOpSetScreenWindow,  // 57
    RoomScriptOpHideScreenWindow,  // 58
    RoomScriptOpSetTileObjectFacing,  // 59
    RoomScriptOpAddQuestState,  // 60
    RoomScriptOpSubtractQuestState,  // 61
    RoomScriptOpClearQuestStateUpperHalf,  // 62
    RoomScriptOpNoOpAlt,  // 63
    RoomScriptOpInvokeChainIfEnabled,  // 64
    RoomScriptOpGrantPartyExperience,  // 65
    RoomScriptOpSetBattleDefeatState,  // 66
    RoomScriptOpSetTileObjectDrawLayer,  // 67
    RoomScriptOpEnterFredAndGeorgesShop,  // 68
    RoomScriptOpFullHealParty,  // 69
    RoomScriptOpRespawnRowAndRunChain,  // 70
    RoomScriptOpStartMinigame,  // 71
    RoomScriptOpDespawnRoomRowObjects,  // 72
    RoomScriptOpGrantPartySpell,  // 73
    RoomScriptOpSetOverworldMonstersDisabled,  // 74
    RoomScriptOpClearOverworldMonstersDisabled,  // 75
    RoomScriptOpSetTileObjectFacingAndScriptPage,  // 76
    RoomScriptOpSetTileObjectSpecialFlag,  // 77
    RoomScriptOpUnlockMinigame,  // 78
    RoomScriptOpShowRewardPickupMessage,  // 79
    RoomScriptOpShowItemRemovedMessage,  // 80
    RoomScriptOpShowSpellLearnedMessage,  // 81
    RoomScriptOpSetPauseMenuLocked,  // 82
    RoomScriptOpGotoIfFolioPageGroupComplete,  // 83
    RoomScriptOpShowFolioCategoryStatusMessage,  // 84
    RoomScriptOpShowMinigameUnlockedMessage,  // 85
    RoomScriptOpShowPartyLevelUpMessage,  // 86
    RoomScriptOpGrantPartyLevelUps,  // 87
    RoomScriptOpUnmuteAllMusicChannels,  // 88
    RoomScriptOpConsumeRoomItem,  // 89
    RoomScriptOpResetPartyLeaderSelection,  // 90
    RoomScriptOpGotoIfAllQuestFlagsSet,  // 91
    RoomScriptOpSetPendingChainFromExitParam,  // 92
};
