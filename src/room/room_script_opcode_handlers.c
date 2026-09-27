#include "types.h"
#include "room_script.h"
#include "room_script_opcodes.h"

// Room-script opcode -> handler table; see docs/formats/room_scripts.md.
// Opcode 0 ends a chain and has no handler.

const RoomScriptOpcodeHandler g_apRoomScriptOpcodeHandlers[93] = {
    0,  // 0: chain terminator
    (RoomScriptOpcodeHandler)RoomScriptOpDespawnTileObject,  // 1
    (RoomScriptOpcodeHandler)RoomScriptOp2,  // 2
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectFlagBit,  // 3
    (RoomScriptOpcodeHandler)RoomScriptOpClearTileObjectFlagBit,  // 4
    (RoomScriptOpcodeHandler)RoomScriptOpShowRoomDialog,  // 5
    RoomScriptOpPauseMusic,  // 6
    RoomScriptOpResumeMusic,  // 7
    (RoomScriptOpcodeHandler)RoomScriptOpPlayMusicModuleAndFlagIfChain1,  // 8
    (RoomScriptOpcodeHandler)RoomScriptOpPlayRoomSoundEffect,  // 9
    (RoomScriptOpcodeHandler)RoomScriptOpPlaySoundById,  // 10
    (RoomScriptOpcodeHandler)RoomScriptOpSetRoomMusicVolume,  // 11
    (RoomScriptOpcodeHandler)RoomScriptOpSetSoundEffectVolume,  // 12
    (RoomScriptOpcodeHandler)RoomScriptOpDelayedRespawnRowAndRunChain,  // 13
    (RoomScriptOpcodeHandler)RoomScriptOpSetStoryStage,  // 14
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectAnimState,  // 15
    RoomScriptOpQueueTileObjectMove,  // 16
    (RoomScriptOpcodeHandler)RoomScriptOpReturnToOverworld,  // 17
    (RoomScriptOpcodeHandler)RoomScriptOpSetAllQueuedMoveParams,  // 18
    RoomScriptOpClearAllQueuedMoves,  // 19
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectPosition,  // 20
    (RoomScriptOpcodeHandler)RoomScriptOpPlayCutscene,  // 21
    (RoomScriptOpcodeHandler)RoomScriptOpCloseRoomDialog,  // 22
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectFollowTarget,  // 23
    (RoomScriptOpcodeHandler)RoomScriptOpStartObjectAnimSequence,  // 24
    (RoomScriptOpcodeHandler)RoomScriptOpStartTileObjectScript,  // 25
    (RoomScriptOpcodeHandler)RoomScriptOpPlayTileObjectAnimation,  // 26
    RoomScriptOpOpenMainMenu,  // 27
    (RoomScriptOpcodeHandler)RoomScriptOpArmChainYield,  // 28
    (RoomScriptOpcodeHandler)RoomScriptOpGotoIfQuestStateCompare,  // 29
    (RoomScriptOpcodeHandler)RoomScriptOpGotoIfQuestStatePairCompare,  // 30
    (RoomScriptOpcodeHandler)RoomScriptOpSetQuestState,  // 31
    (RoomScriptOpcodeHandler)RoomScriptOpCopyQuestState,  // 32
    (RoomScriptOpcodeHandler)RoomScriptOpCancelObjectAnimSequence,  // 33
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectAnimStateWithSpeed,  // 34
    (RoomScriptOpcodeHandler)RoomScriptOpPatchRoomBackgroundTile,  // 35
    (RoomScriptOpcodeHandler)RoomScriptOpShowLoadingScreenTransition,  // 36
    RoomScriptOpPlayScreenTransitionOut,  // 37
    RoomScriptOpPlayScreenTransitionIn,  // 38
    (RoomScriptOpcodeHandler)RoomScriptOpRecruitPartyFollower,  // 39
    (RoomScriptOpcodeHandler)RoomScriptOpRemovePartyFollower,  // 40
    (RoomScriptOpcodeHandler)RoomScriptOpSpawnPartyFollowerAtTile,  // 41
    (RoomScriptOpcodeHandler)RoomScriptOp42,  // 42
    (RoomScriptOpcodeHandler)RoomScriptOpStartBattle,  // 43
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectAnimStateValue,  // 44
    (RoomScriptOpcodeHandler)RoomScriptOpGrantRoomReward,  // 45
    (RoomScriptOpcodeHandler)RoomScriptOpSetBackgroundBlendLayers,  // 46
    (RoomScriptOpcodeHandler)RoomScriptOpShowBackgroundLayer,  // 47
    (RoomScriptOpcodeHandler)RoomScriptOpHideBackgroundLayer,  // 48
    (RoomScriptOpcodeHandler)RoomScriptOpSetBackgroundPriority,  // 49
    (RoomScriptOpcodeHandler)RoomScriptOpSetCameraFollowTileObject,  // 50
    RoomScriptOpPlaySpecialSceneEffect,  // 51
    (RoomScriptOpcodeHandler)RoomScriptOpDelayedRespawnRowAndRunChainFrames,  // 52
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectAndLinkedVisible,  // 53
    (RoomScriptOpcodeHandler)RoomScriptOpGotoIfStoryStageCompare,  // 54
    (RoomScriptOpcodeHandler)RoomScriptOpSetRandomQuestState,  // 55
    RoomScriptOpNoOp,  // 56
    (RoomScriptOpcodeHandler)RoomScriptOpSetScreenWindow,  // 57
    (RoomScriptOpcodeHandler)RoomScriptOpHideScreenWindow,  // 58
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectFacing,  // 59
    (RoomScriptOpcodeHandler)RoomScriptOpAddQuestState,  // 60
    (RoomScriptOpcodeHandler)RoomScriptOpSubtractQuestState,  // 61
    RoomScriptOpClearQuestStateUpperHalf,  // 62
    RoomScriptOpNoOpAlt,  // 63
    (RoomScriptOpcodeHandler)RoomScriptOpInvokeChainIfEnabled,  // 64
    (RoomScriptOpcodeHandler)RoomScriptOpGrantPartyExperience,  // 65
    (RoomScriptOpcodeHandler)RoomScriptOpSetBattleDefeatState,  // 66
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectDrawLayer,  // 67
    (RoomScriptOpcodeHandler)RoomScriptOpEnterFredAndGeorgesShop,  // 68
    RoomScriptOpFullHealParty,  // 69
    (RoomScriptOpcodeHandler)RoomScriptOpRespawnRowAndRunChain,  // 70
    (RoomScriptOpcodeHandler)RoomScriptOpStartMinigame,  // 71
    (RoomScriptOpcodeHandler)RoomScriptOpDespawnRoomRowObjects,  // 72
    (RoomScriptOpcodeHandler)RoomScriptOpGrantPartySpell,  // 73
    RoomScriptOpSetOverworldMonstersDisabled,  // 74
    RoomScriptOpClearOverworldMonstersDisabled,  // 75
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectFacingAndScriptPage,  // 76
    (RoomScriptOpcodeHandler)RoomScriptOpSetTileObjectSpecialFlag,  // 77
    (RoomScriptOpcodeHandler)RoomScriptOpUnlockMinigame,  // 78
    (RoomScriptOpcodeHandler)RoomScriptOpShowRewardPickupMessage,  // 79
    (RoomScriptOpcodeHandler)RoomScriptOpShowItemRemovedMessage,  // 80
    (RoomScriptOpcodeHandler)RoomScriptOpShowSpellLearnedMessage,  // 81
    (RoomScriptOpcodeHandler)RoomScriptOpSetPauseMenuLocked,  // 82
    (RoomScriptOpcodeHandler)RoomScriptOpGotoIfFolioPageGroupComplete,  // 83
    (RoomScriptOpcodeHandler)RoomScriptOpShowFolioCategoryStatusMessage,  // 84
    (RoomScriptOpcodeHandler)RoomScriptOpShowMinigameUnlockedMessage,  // 85
    (RoomScriptOpcodeHandler)RoomScriptOpShowPartyLevelUpMessage,  // 86
    (RoomScriptOpcodeHandler)RoomScriptOpGrantPartyLevelUps,  // 87
    RoomScriptOpUnmuteAllMusicChannels,  // 88
    (RoomScriptOpcodeHandler)RoomScriptOpConsumeRoomItem,  // 89
    RoomScriptOpResetPartyLeaderSelection,  // 90
    (RoomScriptOpcodeHandler)RoomScriptOpGotoIfAllQuestFlagsSet,  // 91
    (RoomScriptOpcodeHandler)RoomScriptOpSetPendingChainFromExitParam,  // 92
};
