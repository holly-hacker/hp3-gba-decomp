#pragma once

// Room-script bytecode; see docs/formats/room_scripts.md. A record is a u32 opcode
// followed by its operand bytes, always a multiple of 4 bytes in total. Each
// RS_<Name>(...) macro expands to the record's bytes. Multi-byte operands are given as
// one value and split little-endian; trailing operand bytes the handler never reads (or
// that are always the same) are filled in by the macro.

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
#define RS_DespawnTileObject(tileX, tileY) RS_OP(RSOP_DespawnTileObject), (tileX), (tileY), (255), (255)
#define RS_Unk02(tileX, tileY, value) RS_OP(RSOP_Unk02), (tileX), (tileY), (((value) >> 0) & 0xFF), (((value) >> 8) & 0xFF)
#define RS_SetTileObjectFlagBit(tileX, tileY, bit) RS_OP(RSOP_SetTileObjectFlagBit), (tileX), (tileY), (bit), (255)
#define RS_ClearTileObjectFlagBit(tileX, tileY, bit) RS_OP(RSOP_ClearTileObjectFlagBit), (tileX), (tileY), (bit), (255)
#define RS_ShowRoomDialog(blockId) RS_OP(RSOP_ShowRoomDialog), (((blockId) >> 0) & 0xFF), (((blockId) >> 8) & 0xFF), (0), (0)
#define RS_PauseMusic() RS_OP(RSOP_PauseMusic)
#define RS_ResumeMusic() RS_OP(RSOP_ResumeMusic)
#define RS_PlayMusicModuleAndFlagIfChain1(moduleId) RS_OP(RSOP_PlayMusicModuleAndFlagIfChain1), (moduleId), (255), (255), (255)
#define RS_PlayRoomSoundEffect(soundId) RS_OP(RSOP_PlayRoomSoundEffect), (soundId), (255), (255), (255)
#define RS_PlaySoundById(soundId) RS_OP(RSOP_PlaySoundById), (soundId), (255), (255), (255)
#define RS_SetRoomMusicVolume(volume, unused0, unused1, unused2) RS_OP(RSOP_SetRoomMusicVolume), (volume), (unused0), (unused1), (unused2)
#define RS_SetSoundEffectVolume(volume, unused0, unused1, unused2) RS_OP(RSOP_SetSoundEffectVolume), (volume), (unused0), (unused1), (unused2)
#define RS_DelayedRespawnRowAndRunChain(delay, respawnRow, chainRow) RS_OP(RSOP_DelayedRespawnRowAndRunChain), (((delay) >> 0) & 0xFF), (((delay) >> 8) & 0xFF), (respawnRow), (chainRow)
#define RS_SetStoryStage(stage) RS_OP(RSOP_SetStoryStage), (stage), (255), (255), (255)
#define RS_SetTileObjectAnimState(tileX, tileY) RS_OP(RSOP_SetTileObjectAnimState), (tileX), (tileY), (255), (255)
#define RS_QueueTileObjectMove(x, y, byte1, byte2, speed, unknown) RS_OP(RSOP_QueueTileObjectMove), (x), (y), (byte1), (byte2), (((speed) >> 0) & 0xFF), (((speed) >> 8) & 0xFF), (((unknown) >> 0) & 0xFF), (((unknown) >> 8) & 0xFF)
#define RS_ReturnToOverworld(exitId, exitParam) RS_OP(RSOP_ReturnToOverworld), (exitId), (exitParam), (255), (255)
#define RS_SetAllQueuedMoveParams(duration, amplitude, respawnRow, chainRow, unused) RS_OP(RSOP_SetAllQueuedMoveParams), (((duration) >> 0) & 0xFF), (((duration) >> 8) & 0xFF), (((amplitude) >> 0) & 0xFF), (((amplitude) >> 8) & 0xFF), (respawnRow), (chainRow), (((unused) >> 0) & 0xFF), (((unused) >> 8) & 0xFF)
#define RS_ClearAllQueuedMoves() RS_OP(RSOP_ClearAllQueuedMoves)
#define RS_SetTileObjectPosition(x, y, tileX, tileY, facing, unused) RS_OP(RSOP_SetTileObjectPosition), (((x) >> 0) & 0xFF), (((x) >> 8) & 0xFF), (((y) >> 0) & 0xFF), (((y) >> 8) & 0xFF), (tileX), (tileY), (facing), (unused)
#define RS_PlayCutscene(cutsceneId, pendingRow, pendingChain) RS_OP(RSOP_PlayCutscene), (cutsceneId), (pendingRow), (pendingChain), (255)
#define RS_CloseRoomDialog(unused0, exitParam, unused1, unused2) RS_OP(RSOP_CloseRoomDialog), (unused0), (exitParam), (unused1), (unused2)
#define RS_SetTileObjectFollowTarget(tileX, tileY, targetTileX, targetTileY, useTargetTile, resumeDistance, stopDistance, unused) RS_OP(RSOP_SetTileObjectFollowTarget), (tileX), (tileY), (targetTileX), (targetTileY), (useTargetTile), (resumeDistance), (stopDistance), (unused)
#define RS_StartObjectAnimSequence(x, y, effectId, localA, localB, unk65, animStateSelector, stateByte0x60, flagsA, flagsB) RS_OP(RSOP_StartObjectAnimSequence), (x), (y), (effectId), (localA), (localB), (unk65), (animStateSelector), (stateByte0x60), (flagsA), (flagsB), (255), (255)
#define RS_StartTileObjectScript(scriptPC, effectId, localA, tileX, tileY, arg65, arg66, arg64, unused0, unused1, unused2) RS_OP(RSOP_StartTileObjectScript), (((scriptPC) >> 0) & 0xFF), (((scriptPC) >> 8) & 0xFF), (effectId), (localA), (tileX), (tileY), (arg65), (arg66), (arg64), (unused0), (unused1), (unused2)
#define RS_PlayTileObjectAnimation(tileX, tileY, animId) RS_OP(RSOP_PlayTileObjectAnimation), (tileX), (tileY), (((animId) >> 0) & 0xFF), (((animId) >> 8) & 0xFF)
#define RS_OpenMainMenu() RS_OP(RSOP_OpenMainMenu)
#define RS_ArmChainYield(arm) RS_OP(RSOP_ArmChainYield), (arm), (255), (255), (255)
#define RS_GotoIfQuestStateCompare(index, cmpOp, value, trueChain, falseChain, trueRow, falseRow) RS_OP(RSOP_GotoIfQuestStateCompare), (index), (cmpOp), (value), (trueChain), (falseChain), (trueRow), (falseRow), (255)
#define RS_GotoIfQuestStatePairCompare(indexA, cmpOp, indexB, trueChain, falseChain, trueRow, falseRow) RS_OP(RSOP_GotoIfQuestStatePairCompare), (indexA), (cmpOp), (indexB), (trueChain), (falseChain), (trueRow), (falseRow), (255)
#define RS_SetQuestState(value, index) RS_OP(RSOP_SetQuestState), (value), (index), (255), (255)
#define RS_CopyQuestState(srcIndex, dstIndex, unused0, unused1) RS_OP(RSOP_CopyQuestState), (srcIndex), (dstIndex), (unused0), (unused1)
#define RS_CancelObjectAnimSequence(tileX, tileY) RS_OP(RSOP_CancelObjectAnimSequence), (tileX), (tileY), (255), (255)
#define RS_SetTileObjectAnimStateWithSpeed(tileX, tileY) RS_OP(RSOP_SetTileObjectAnimStateWithSpeed), (tileX), (tileY), (255), (255)
#define RS_PatchRoomBackgroundTile(x, y, tileId, layer, unused) RS_OP(RSOP_PatchRoomBackgroundTile), (((x) >> 0) & 0xFF), (((x) >> 8) & 0xFF), (((y) >> 0) & 0xFF), (((y) >> 8) & 0xFF), (((tileId) >> 0) & 0xFF), (((tileId) >> 8) & 0xFF), (layer), (unused)
#define RS_ShowLoadingScreenTransition(modeArg1, modeArg2, modeArg3, unused) RS_OP(RSOP_ShowLoadingScreenTransition), (modeArg1), (modeArg2), (modeArg3), (unused)
#define RS_PlayScreenTransitionOut() RS_OP(RSOP_PlayScreenTransitionOut)
#define RS_PlayScreenTransitionIn() RS_OP(RSOP_PlayScreenTransitionIn)
#define RS_RecruitPartyFollower(characterId) RS_OP(RSOP_RecruitPartyFollower), (characterId), (255), (255), (255)
#define RS_RemovePartyFollower(characterId) RS_OP(RSOP_RemovePartyFollower), (characterId), (255), (255), (255)
#define RS_SpawnPartyFollowerAtTile(characterId, tileX, tileY, unused) RS_OP(RSOP_SpawnPartyFollowerAtTile), (characterId), (tileX), (tileY), (unused)
#define RS_Unk2A(arg, unused0, unused1, unused2) RS_OP(RSOP_Unk2A), (arg), (unused0), (unused1), (unused2)
#define RS_StartBattle(battleId, pendingRow, pendingChain) RS_OP(RSOP_StartBattle), (battleId), (pendingRow), (pendingChain), (255)
#define RS_SetTileObjectAnimStateValue(tileX, tileY, actionState) RS_OP(RSOP_SetTileObjectAnimStateValue), (tileX), (tileY), (actionState), (255)
#define RS_GrantRoomReward(rewardId, variant) RS_OP(RSOP_GrantRoomReward), (rewardId), (variant), (255), (255)
#define RS_SetBackgroundBlendLayers(bg0, bg1, bg2, bg3) RS_OP(RSOP_SetBackgroundBlendLayers), (bg0), (bg1), (bg2), (bg3)
#define RS_ShowBackgroundLayer(bg, unused0, unused1, unused2) RS_OP(RSOP_ShowBackgroundLayer), (bg), (unused0), (unused1), (unused2)
#define RS_HideBackgroundLayer(bg) RS_OP(RSOP_HideBackgroundLayer), (bg), (255), (255), (255)
#define RS_SetBackgroundPriority(bg, priority, unused0, unused1) RS_OP(RSOP_SetBackgroundPriority), (bg), (priority), (unused0), (unused1)
#define RS_SetCameraFollowTileObject(tileX, tileY, unused0, unused1) RS_OP(RSOP_SetCameraFollowTileObject), (tileX), (tileY), (unused0), (unused1)
#define RS_PlaySpecialSceneEffect(mode) RS_OP(RSOP_PlaySpecialSceneEffect), (mode), (255), (255), (255)
#define RS_DelayedRespawnRowAndRunChainFrames(delay, respawnRow, chainRow) RS_OP(RSOP_DelayedRespawnRowAndRunChainFrames), (((delay) >> 0) & 0xFF), (((delay) >> 8) & 0xFF), (respawnRow), (chainRow)
#define RS_SetTileObjectAndLinkedVisible(tileX, tileY, visible, unused) RS_OP(RSOP_SetTileObjectAndLinkedVisible), (tileX), (tileY), (visible), (unused)
#define RS_GotoIfStoryStageCompare(cmpOp, value, trueChain, falseChain, trueRow, falseRow) RS_OP(RSOP_GotoIfStoryStageCompare), (cmpOp), (value), (trueChain), (falseChain), (trueRow), (falseRow), (255), (255)
#define RS_SetRandomQuestState(min, max, index, unused0, unused1, unused2) RS_OP(RSOP_SetRandomQuestState), (((min) >> 0) & 0xFF), (((min) >> 8) & 0xFF), (((max) >> 0) & 0xFF), (((max) >> 8) & 0xFF), (index), (unused0), (unused1), (unused2)
#define RS_NoOp(unknown) RS_OP(RSOP_NoOp), (((unknown) >> 0) & 0xFF), (((unknown) >> 8) & 0xFF), (((unknown) >> 16) & 0xFF), (((unknown) >> 24) & 0xFF)
#define RS_SetScreenWindow(windowId, unused0, x0, y0, x1, y1, winIn, winOut, unused1) RS_OP(RSOP_SetScreenWindow), (windowId), (unused0), (((x0) >> 0) & 0xFF), (((x0) >> 8) & 0xFF), (((y0) >> 0) & 0xFF), (((y0) >> 8) & 0xFF), (((x1) >> 0) & 0xFF), (((x1) >> 8) & 0xFF), (((y1) >> 0) & 0xFF), (((y1) >> 8) & 0xFF), (winIn), (winOut), (((unused1) >> 0) & 0xFF), (((unused1) >> 8) & 0xFF), (((unused1) >> 16) & 0xFF), (((unused1) >> 24) & 0xFF)
#define RS_HideScreenWindow(windowId, unused0, unused1, unused2) RS_OP(RSOP_HideScreenWindow), (windowId), (unused0), (unused1), (unused2)
#define RS_SetTileObjectFacing(tileX, tileY, facing) RS_OP(RSOP_SetTileObjectFacing), (tileX), (tileY), (facing), (255)
#define RS_AddQuestState(amount, index) RS_OP(RSOP_AddQuestState), (amount), (index), (255), (255)
#define RS_SubtractQuestState(amount, index) RS_OP(RSOP_SubtractQuestState), (amount), (index), (255), (255)
#define RS_ClearQuestStateUpperHalf() RS_OP(RSOP_ClearQuestStateUpperHalf)
#define RS_NoOpAlt(unknown) RS_OP(RSOP_NoOpAlt), (((unknown) >> 0) & 0xFF), (((unknown) >> 8) & 0xFF), (((unknown) >> 16) & 0xFF), (((unknown) >> 24) & 0xFF)
#define RS_InvokeChainIfEnabled(row, chain) RS_OP(RSOP_InvokeChainIfEnabled), (row), (chain), (255), (255)
#define RS_GrantPartyExperience(experience, unused) RS_OP(RSOP_GrantPartyExperience), (((experience) >> 0) & 0xFF), (((experience) >> 8) & 0xFF), (((unused) >> 0) & 0xFF), (((unused) >> 8) & 0xFF)
#define RS_SetBattleDefeatState(value) RS_OP(RSOP_SetBattleDefeatState), (value), (255), (255), (255)
#define RS_SetTileObjectDrawLayer(tileX, tileY, priority, unused) RS_OP(RSOP_SetTileObjectDrawLayer), (tileX), (tileY), (priority), (unused)
#define RS_EnterFredAndGeorgesShop(modeArg, pendingRow, pendingChain) RS_OP(RSOP_EnterFredAndGeorgesShop), (modeArg), (pendingRow), (pendingChain), (255)
#define RS_FullHealParty() RS_OP(RSOP_FullHealParty)
#define RS_RespawnRowAndRunChain(respawnRow, chainRow) RS_OP(RSOP_RespawnRowAndRunChain), (respawnRow), (chainRow), (255), (255)
#define RS_StartMinigame(minigameId, param, showHelp, pendingRow, pendingChain) RS_OP(RSOP_StartMinigame), (minigameId), (param), (showHelp), (pendingRow), (pendingChain), (255), (255), (255)
#define RS_DespawnRoomRowObjects(row) RS_OP(RSOP_DespawnRoomRowObjects), (row), (255), (255), (255)
#define RS_GrantPartySpell(characterId) RS_OP(RSOP_GrantPartySpell), (characterId), (255), (255), (255)
#define RS_SetOverworldMonstersDisabled() RS_OP(RSOP_SetOverworldMonstersDisabled)
#define RS_ClearOverworldMonstersDisabled() RS_OP(RSOP_ClearOverworldMonstersDisabled)
#define RS_SetTileObjectFacingAndScriptPage(tileX, tileY, facing, scriptPageHigh) RS_OP(RSOP_SetTileObjectFacingAndScriptPage), (tileX), (tileY), (facing), (scriptPageHigh)
#define RS_SetTileObjectSpecialFlag(tileX, tileY, set) RS_OP(RSOP_SetTileObjectSpecialFlag), (tileX), (tileY), (set), (255)
#define RS_UnlockMinigame(minigameId) RS_OP(RSOP_UnlockMinigame), (minigameId), (255), (255), (255)
#define RS_ShowRewardPickupMessage(rewardId) RS_OP(RSOP_ShowRewardPickupMessage), (rewardId), (0), (0), (255)
#define RS_ShowItemRemovedMessage(rewardId) RS_OP(RSOP_ShowItemRemovedMessage), (rewardId), (0), (0), (255)
#define RS_ShowSpellLearnedMessage(spellId, skipIfSaveFlag) RS_OP(RSOP_ShowSpellLearnedMessage), (spellId), (skipIfSaveFlag), (0), (0)
#define RS_SetPauseMenuLocked(locked, unused0, unused1, unused2) RS_OP(RSOP_SetPauseMenuLocked), (locked), (unused0), (unused1), (unused2)
#define RS_GotoIfFolioPageGroupComplete(pageGroupId, trueRow, trueChain, falseRow, falseChain, unused0, unused1, unused2) RS_OP(RSOP_GotoIfFolioPageGroupComplete), (pageGroupId), (trueRow), (trueChain), (falseRow), (falseChain), (unused0), (unused1), (unused2)
#define RS_ShowFolioCategoryStatusMessage(category, complete) RS_OP(RSOP_ShowFolioCategoryStatusMessage), (category), (complete), (0), (0)
#define RS_ShowMinigameUnlockedMessage(minigameId) RS_OP(RSOP_ShowMinigameUnlockedMessage), (minigameId), (0), (0), (255)
#define RS_ShowPartyLevelUpMessage(levelCount) RS_OP(RSOP_ShowPartyLevelUpMessage), (levelCount), (0), (0), (255)
#define RS_GrantPartyLevelUps(levelCount) RS_OP(RSOP_GrantPartyLevelUps), (levelCount), (255), (255), (255)
#define RS_UnmuteAllMusicChannels() RS_OP(RSOP_UnmuteAllMusicChannels)
#define RS_ConsumeRoomItem(itemId) RS_OP(RSOP_ConsumeRoomItem), (itemId), (255), (255), (255)
#define RS_ResetPartyLeaderSelection() RS_OP(RSOP_ResetPartyLeaderSelection)
#define RS_GotoIfAllQuestFlagsSet(trueChain, falseChain, trueRow, falseRow) RS_OP(RSOP_GotoIfAllQuestFlagsSet), (trueChain), (falseChain), (trueRow), (falseRow)
#define RS_SetPendingChainFromExitParam(chainIfExit1, chainIfExit0, unused0, unused1) RS_OP(RSOP_SetPendingChainFromExitParam), (chainIfExit1), (chainIfExit0), (unused0), (unused1)
