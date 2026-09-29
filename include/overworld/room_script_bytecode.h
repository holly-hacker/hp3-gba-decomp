#pragma once

// Room-script bytecode; see docs/formats/room_scripts.md. A record is a u32 opcode
// followed by its operand bytes, always a multiple of 4 bytes in total. Each
// RS_<Name>(...) macro expands to the record's bytes; the operand count is fixed
// per opcode and checked by the preprocessor.

enum RoomScriptOpcode {
    RSOP_End = 0,
    RSOP_DespawnTileObject = 1,
    RSOP_Unk02 = 2,
    RSOP_SetTileObjectFlagBit = 3,
    RSOP_ClearTileObjectFlagBit = 4,
    RSOP_ShowRoomDialog = 5,
    RSOP_PauseMusic = 6,
    RSOP_ResumeMusic = 7,
    RSOP_PlayMusicModuleAndFlagIfChain1 = 8,
    RSOP_PlayRoomSoundEffect = 9,
    RSOP_PlaySoundById = 10,
    RSOP_SetRoomMusicVolume = 11,
    RSOP_SetSoundEffectVolume = 12,
    RSOP_DelayedRespawnRowAndRunChain = 13,
    RSOP_SetStoryStage = 14,
    RSOP_SetTileObjectAnimState = 15,
    RSOP_QueueTileObjectMove = 16,
    RSOP_ReturnToOverworld = 17,
    RSOP_SetAllQueuedMoveParams = 18,
    RSOP_ClearAllQueuedMoves = 19,
    RSOP_SetTileObjectPosition = 20,
    RSOP_PlayCutscene = 21,
    RSOP_CloseRoomDialog = 22,
    RSOP_SetTileObjectFollowTarget = 23,
    RSOP_StartObjectAnimSequence = 24,
    RSOP_StartTileObjectScript = 25,
    RSOP_PlayTileObjectAnimation = 26,
    RSOP_OpenMainMenu = 27,
    RSOP_ArmChainYield = 28,
    RSOP_GotoIfQuestStateCompare = 29,
    RSOP_GotoIfQuestStatePairCompare = 30,
    RSOP_SetQuestState = 31,
    RSOP_CopyQuestState = 32,
    RSOP_CancelObjectAnimSequence = 33,
    RSOP_SetTileObjectAnimStateWithSpeed = 34,
    RSOP_PatchRoomBackgroundTile = 35,
    RSOP_ShowLoadingScreenTransition = 36,
    RSOP_PlayScreenTransitionOut = 37,
    RSOP_PlayScreenTransitionIn = 38,
    RSOP_RecruitPartyFollower = 39,
    RSOP_RemovePartyFollower = 40,
    RSOP_SpawnPartyFollowerAtTile = 41,
    RSOP_Unk2A = 42,
    RSOP_StartBattle = 43,
    RSOP_SetTileObjectAnimStateValue = 44,
    RSOP_GrantRoomReward = 45,
    RSOP_SetBackgroundBlendLayers = 46,
    RSOP_ShowBackgroundLayer = 47,
    RSOP_HideBackgroundLayer = 48,
    RSOP_SetBackgroundPriority = 49,
    RSOP_SetCameraFollowTileObject = 50,
    RSOP_PlaySpecialSceneEffect = 51,
    RSOP_DelayedRespawnRowAndRunChainFrames = 52,
    RSOP_SetTileObjectAndLinkedVisible = 53,
    RSOP_GotoIfStoryStageCompare = 54,
    RSOP_SetRandomQuestState = 55,
    RSOP_NoOp = 56,
    RSOP_SetScreenWindow = 57,
    RSOP_HideScreenWindow = 58,
    RSOP_SetTileObjectFacing = 59,
    RSOP_AddQuestState = 60,
    RSOP_SubtractQuestState = 61,
    RSOP_ClearQuestStateUpperHalf = 62,
    RSOP_NoOpAlt = 63,
    RSOP_InvokeChainIfEnabled = 64,
    RSOP_GrantPartyExperience = 65,
    RSOP_SetBattleDefeatState = 66,
    RSOP_SetTileObjectDrawLayer = 67,
    RSOP_EnterFredAndGeorgesShop = 68,
    RSOP_FullHealParty = 69,
    RSOP_RespawnRowAndRunChain = 70,
    RSOP_StartMinigame = 71,
    RSOP_DespawnRoomRowObjects = 72,
    RSOP_GrantPartySpell = 73,
    RSOP_SetOverworldMonstersDisabled = 74,
    RSOP_ClearOverworldMonstersDisabled = 75,
    RSOP_SetTileObjectFacingAndScriptPage = 76,
    RSOP_SetTileObjectSpecialFlag = 77,
    RSOP_UnlockMinigame = 78,
    RSOP_ShowRewardPickupMessage = 79,
    RSOP_ShowItemRemovedMessage = 80,
    RSOP_ShowSpellLearnedMessage = 81,
    RSOP_SetPauseMenuLocked = 82,
    RSOP_GotoIfFolioPageGroupComplete = 83,
    RSOP_ShowFolioCategoryStatusMessage = 84,
    RSOP_ShowMinigameUnlockedMessage = 85,
    RSOP_ShowPartyLevelUpMessage = 86,
    RSOP_GrantPartyLevelUps = 87,
    RSOP_UnmuteAllMusicChannels = 88,
    RSOP_ConsumeRoomItem = 89,
    RSOP_ResetPartyLeaderSelection = 90,
    RSOP_GotoIfAllQuestFlagsSet = 91,
    RSOP_SetPendingChainFromExitParam = 92,
    RSOP_COUNT = 93,
};

#define RS_OP(op) (op), 0, 0, 0

#define RS_End() RS_OP(RSOP_End)
#define RS_DespawnTileObject(a, b, c, d) RS_OP(RSOP_DespawnTileObject), (a), (b), (c), (d)
#define RS_Unk02(a, b, c, d) RS_OP(RSOP_Unk02), (a), (b), (c), (d)
#define RS_SetTileObjectFlagBit(a, b, c, d) RS_OP(RSOP_SetTileObjectFlagBit), (a), (b), (c), (d)
#define RS_ClearTileObjectFlagBit(a, b, c, d) RS_OP(RSOP_ClearTileObjectFlagBit), (a), (b), (c), (d)
#define RS_ShowRoomDialog(a, b, c, d) RS_OP(RSOP_ShowRoomDialog), (a), (b), (c), (d)
#define RS_PauseMusic() RS_OP(RSOP_PauseMusic)
#define RS_ResumeMusic() RS_OP(RSOP_ResumeMusic)
#define RS_PlayMusicModuleAndFlagIfChain1(a, b, c, d) RS_OP(RSOP_PlayMusicModuleAndFlagIfChain1), (a), (b), (c), (d)
#define RS_PlayRoomSoundEffect(a, b, c, d) RS_OP(RSOP_PlayRoomSoundEffect), (a), (b), (c), (d)
#define RS_PlaySoundById(a, b, c, d) RS_OP(RSOP_PlaySoundById), (a), (b), (c), (d)
#define RS_SetRoomMusicVolume(a, b, c, d) RS_OP(RSOP_SetRoomMusicVolume), (a), (b), (c), (d)
#define RS_SetSoundEffectVolume(a, b, c, d) RS_OP(RSOP_SetSoundEffectVolume), (a), (b), (c), (d)
#define RS_DelayedRespawnRowAndRunChain(a, b, c, d) RS_OP(RSOP_DelayedRespawnRowAndRunChain), (a), (b), (c), (d)
#define RS_SetStoryStage(a, b, c, d) RS_OP(RSOP_SetStoryStage), (a), (b), (c), (d)
#define RS_SetTileObjectAnimState(a, b, c, d) RS_OP(RSOP_SetTileObjectAnimState), (a), (b), (c), (d)
#define RS_QueueTileObjectMove(a, b, c, d, e, f, g, h) RS_OP(RSOP_QueueTileObjectMove), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_ReturnToOverworld(a, b, c, d) RS_OP(RSOP_ReturnToOverworld), (a), (b), (c), (d)
#define RS_SetAllQueuedMoveParams(a, b, c, d, e, f, g, h) RS_OP(RSOP_SetAllQueuedMoveParams), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_ClearAllQueuedMoves() RS_OP(RSOP_ClearAllQueuedMoves)
#define RS_SetTileObjectPosition(a, b, c, d, e, f, g, h) RS_OP(RSOP_SetTileObjectPosition), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_PlayCutscene(a, b, c, d) RS_OP(RSOP_PlayCutscene), (a), (b), (c), (d)
#define RS_CloseRoomDialog(a, b, c, d) RS_OP(RSOP_CloseRoomDialog), (a), (b), (c), (d)
#define RS_SetTileObjectFollowTarget(a, b, c, d, e, f, g, h) RS_OP(RSOP_SetTileObjectFollowTarget), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_StartObjectAnimSequence(a, b, c, d, e, f, g, h, i, j, k, l) RS_OP(RSOP_StartObjectAnimSequence), (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l)
#define RS_StartTileObjectScript(a, b, c, d, e, f, g, h, i, j, k, l) RS_OP(RSOP_StartTileObjectScript), (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l)
#define RS_PlayTileObjectAnimation(a, b, c, d) RS_OP(RSOP_PlayTileObjectAnimation), (a), (b), (c), (d)
#define RS_OpenMainMenu() RS_OP(RSOP_OpenMainMenu)
#define RS_ArmChainYield(a, b, c, d) RS_OP(RSOP_ArmChainYield), (a), (b), (c), (d)
#define RS_GotoIfQuestStateCompare(a, b, c, d, e, f, g, h) RS_OP(RSOP_GotoIfQuestStateCompare), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_GotoIfQuestStatePairCompare(a, b, c, d, e, f, g, h) RS_OP(RSOP_GotoIfQuestStatePairCompare), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_SetQuestState(a, b, c, d) RS_OP(RSOP_SetQuestState), (a), (b), (c), (d)
#define RS_CopyQuestState(a, b, c, d) RS_OP(RSOP_CopyQuestState), (a), (b), (c), (d)
#define RS_CancelObjectAnimSequence(a, b, c, d) RS_OP(RSOP_CancelObjectAnimSequence), (a), (b), (c), (d)
#define RS_SetTileObjectAnimStateWithSpeed(a, b, c, d) RS_OP(RSOP_SetTileObjectAnimStateWithSpeed), (a), (b), (c), (d)
#define RS_PatchRoomBackgroundTile(a, b, c, d, e, f, g, h) RS_OP(RSOP_PatchRoomBackgroundTile), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_ShowLoadingScreenTransition(a, b, c, d) RS_OP(RSOP_ShowLoadingScreenTransition), (a), (b), (c), (d)
#define RS_PlayScreenTransitionOut() RS_OP(RSOP_PlayScreenTransitionOut)
#define RS_PlayScreenTransitionIn() RS_OP(RSOP_PlayScreenTransitionIn)
#define RS_RecruitPartyFollower(a, b, c, d) RS_OP(RSOP_RecruitPartyFollower), (a), (b), (c), (d)
#define RS_RemovePartyFollower(a, b, c, d) RS_OP(RSOP_RemovePartyFollower), (a), (b), (c), (d)
#define RS_SpawnPartyFollowerAtTile(a, b, c, d) RS_OP(RSOP_SpawnPartyFollowerAtTile), (a), (b), (c), (d)
#define RS_Unk2A(a, b, c, d) RS_OP(RSOP_Unk2A), (a), (b), (c), (d)
#define RS_StartBattle(a, b, c, d) RS_OP(RSOP_StartBattle), (a), (b), (c), (d)
#define RS_SetTileObjectAnimStateValue(a, b, c, d) RS_OP(RSOP_SetTileObjectAnimStateValue), (a), (b), (c), (d)
#define RS_GrantRoomReward(a, b, c, d) RS_OP(RSOP_GrantRoomReward), (a), (b), (c), (d)
#define RS_SetBackgroundBlendLayers(a, b, c, d) RS_OP(RSOP_SetBackgroundBlendLayers), (a), (b), (c), (d)
#define RS_ShowBackgroundLayer(a, b, c, d) RS_OP(RSOP_ShowBackgroundLayer), (a), (b), (c), (d)
#define RS_HideBackgroundLayer(a, b, c, d) RS_OP(RSOP_HideBackgroundLayer), (a), (b), (c), (d)
#define RS_SetBackgroundPriority(a, b, c, d) RS_OP(RSOP_SetBackgroundPriority), (a), (b), (c), (d)
#define RS_SetCameraFollowTileObject(a, b, c, d) RS_OP(RSOP_SetCameraFollowTileObject), (a), (b), (c), (d)
#define RS_PlaySpecialSceneEffect(a, b, c, d) RS_OP(RSOP_PlaySpecialSceneEffect), (a), (b), (c), (d)
#define RS_DelayedRespawnRowAndRunChainFrames(a, b, c, d) RS_OP(RSOP_DelayedRespawnRowAndRunChainFrames), (a), (b), (c), (d)
#define RS_SetTileObjectAndLinkedVisible(a, b, c, d) RS_OP(RSOP_SetTileObjectAndLinkedVisible), (a), (b), (c), (d)
#define RS_GotoIfStoryStageCompare(a, b, c, d, e, f, g, h) RS_OP(RSOP_GotoIfStoryStageCompare), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_SetRandomQuestState(a, b, c, d, e, f, g, h) RS_OP(RSOP_SetRandomQuestState), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_NoOp(a, b, c, d) RS_OP(RSOP_NoOp), (a), (b), (c), (d)
#define RS_SetScreenWindow(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) RS_OP(RSOP_SetScreenWindow), (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l), (m), (n), (o), (p)
#define RS_HideScreenWindow(a, b, c, d) RS_OP(RSOP_HideScreenWindow), (a), (b), (c), (d)
#define RS_SetTileObjectFacing(a, b, c, d) RS_OP(RSOP_SetTileObjectFacing), (a), (b), (c), (d)
#define RS_AddQuestState(a, b, c, d) RS_OP(RSOP_AddQuestState), (a), (b), (c), (d)
#define RS_SubtractQuestState(a, b, c, d) RS_OP(RSOP_SubtractQuestState), (a), (b), (c), (d)
#define RS_ClearQuestStateUpperHalf() RS_OP(RSOP_ClearQuestStateUpperHalf)
#define RS_NoOpAlt(a, b, c, d) RS_OP(RSOP_NoOpAlt), (a), (b), (c), (d)
#define RS_InvokeChainIfEnabled(a, b, c, d) RS_OP(RSOP_InvokeChainIfEnabled), (a), (b), (c), (d)
#define RS_GrantPartyExperience(a, b, c, d) RS_OP(RSOP_GrantPartyExperience), (a), (b), (c), (d)
#define RS_SetBattleDefeatState(a, b, c, d) RS_OP(RSOP_SetBattleDefeatState), (a), (b), (c), (d)
#define RS_SetTileObjectDrawLayer(a, b, c, d) RS_OP(RSOP_SetTileObjectDrawLayer), (a), (b), (c), (d)
#define RS_EnterFredAndGeorgesShop(a, b, c, d) RS_OP(RSOP_EnterFredAndGeorgesShop), (a), (b), (c), (d)
#define RS_FullHealParty() RS_OP(RSOP_FullHealParty)
#define RS_RespawnRowAndRunChain(a, b, c, d) RS_OP(RSOP_RespawnRowAndRunChain), (a), (b), (c), (d)
#define RS_StartMinigame(a, b, c, d, e, f, g, h) RS_OP(RSOP_StartMinigame), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_DespawnRoomRowObjects(a, b, c, d) RS_OP(RSOP_DespawnRoomRowObjects), (a), (b), (c), (d)
#define RS_GrantPartySpell(a, b, c, d) RS_OP(RSOP_GrantPartySpell), (a), (b), (c), (d)
#define RS_SetOverworldMonstersDisabled() RS_OP(RSOP_SetOverworldMonstersDisabled)
#define RS_ClearOverworldMonstersDisabled() RS_OP(RSOP_ClearOverworldMonstersDisabled)
#define RS_SetTileObjectFacingAndScriptPage(a, b, c, d) RS_OP(RSOP_SetTileObjectFacingAndScriptPage), (a), (b), (c), (d)
#define RS_SetTileObjectSpecialFlag(a, b, c, d) RS_OP(RSOP_SetTileObjectSpecialFlag), (a), (b), (c), (d)
#define RS_UnlockMinigame(a, b, c, d) RS_OP(RSOP_UnlockMinigame), (a), (b), (c), (d)
#define RS_ShowRewardPickupMessage(a, b, c, d) RS_OP(RSOP_ShowRewardPickupMessage), (a), (b), (c), (d)
#define RS_ShowItemRemovedMessage(a, b, c, d) RS_OP(RSOP_ShowItemRemovedMessage), (a), (b), (c), (d)
#define RS_ShowSpellLearnedMessage(a, b, c, d) RS_OP(RSOP_ShowSpellLearnedMessage), (a), (b), (c), (d)
#define RS_SetPauseMenuLocked(a, b, c, d) RS_OP(RSOP_SetPauseMenuLocked), (a), (b), (c), (d)
#define RS_GotoIfFolioPageGroupComplete(a, b, c, d, e, f, g, h) RS_OP(RSOP_GotoIfFolioPageGroupComplete), (a), (b), (c), (d), (e), (f), (g), (h)
#define RS_ShowFolioCategoryStatusMessage(a, b, c, d) RS_OP(RSOP_ShowFolioCategoryStatusMessage), (a), (b), (c), (d)
#define RS_ShowMinigameUnlockedMessage(a, b, c, d) RS_OP(RSOP_ShowMinigameUnlockedMessage), (a), (b), (c), (d)
#define RS_ShowPartyLevelUpMessage(a, b, c, d) RS_OP(RSOP_ShowPartyLevelUpMessage), (a), (b), (c), (d)
#define RS_GrantPartyLevelUps(a, b, c, d) RS_OP(RSOP_GrantPartyLevelUps), (a), (b), (c), (d)
#define RS_UnmuteAllMusicChannels() RS_OP(RSOP_UnmuteAllMusicChannels)
#define RS_ConsumeRoomItem(a, b, c, d) RS_OP(RSOP_ConsumeRoomItem), (a), (b), (c), (d)
#define RS_ResetPartyLeaderSelection() RS_OP(RSOP_ResetPartyLeaderSelection)
#define RS_GotoIfAllQuestFlagsSet(a, b, c, d) RS_OP(RSOP_GotoIfAllQuestFlagsSet), (a), (b), (c), (d)
#define RS_SetPendingChainFromExitParam(a, b, c, d) RS_OP(RSOP_SetPendingChainFromExitParam), (a), (b), (c), (d)
