@ Room-script bytecode macros, run by RunRoomScriptChain.
@ A record is a u32 opcode followed by its operand bytes, always a multiple of
@ 4 bytes in total. Multi-byte operands are given as one value and split
@ little-endian; trailing operand bytes the handler never reads (or that are
@ always the same) are filled in by the macro.
@ (group, member) names a room actor (GetRoomActorPtr). "Branches" means
@ CompareAndBranchRoomScript: it calls the taken side's chain (a zero falseChain
@ means none) and spawns the taken row's missing actors if ShouldRunRoomIndex
@ allows it; the walk returns to the caller when that chain ends. "Yields" means
@ the walk stops after the opcode when ArmChainYield 1 preceded it.

@ Fixed indices into g_abQuestEventState (quest event state). Keep these in sync with the QUEST_* defines in
@ include/overworld/room.h.
.set QUEST_STORY_STAGE, 0x00
.set QUEST_DEFEAT_WARP_SELECTOR, 0x10
.set QUEST_CASTLE_AREA, 0x11
.set QUEST_PREV_STORY_STAGE, 0x12
.set QUEST_FOLIO_REWARD_FIRST, 0x14
.set QUEST_FOLIO_REWARD_LAST, 0x18
.set QUEST_OBJECTIVE_INDEX, 0x19
.set QUEST_ALT_PRESENTATION, 0x1A
.set QUEST_CAMERA_Y_OFFSET, 0x1B
.set QUEST_COMPLETION_COUNT, 0x1C
.set QUEST_ROOM_BG_VARIANT, 0x1D
.set QUEST_UPPER_HALF_FIRST, 0x80
.set QUEST_SPAWN_ID_COPY, 0xFE
.set QUEST_SCRATCH_RESULT, 0xFF

@ Leaky Cauldron cellar event flags. Indices 0xDF-0xFD are chapter-scoped scratch: most are reused
@ with different meanings in different chapters, so only indices used by a single event are named.
.set QUEST_CELLAR2_XP5_GIVEN, 0xEE
.set QUEST_CELLAR2_XP20_GIVEN, 0xEF
.set QUEST_CELLAR2_CROOKSHANKS_CAUGHT, 0xF2
.set QUEST_CELLAR1_RAT_TONIC_FOUND, 0xF3
.set QUEST_CELLAR1_INTRO_DIALOG_SHOWN, 0xF7
.set QUEST_CELLAR2_SCABBERS_CAUGHT, 0xFC

@ Main-menu objective values for QUEST_OBJECTIVE_INDEX (dialog text 0x924 + value).
@ Names follow the objective text; _UNUSED values are never set by any room script.
.set QUEST_OBJ_TALK_TO_FUDGE_UNUSED, 0
.set QUEST_OBJ_FIND_HARRYS_ROOM_UNUSED, 1
.set QUEST_OBJ_GREET_WEASLEYS, 2
.set QUEST_OBJ_TALK_TO_TOM_UNUSED, 3
.set QUEST_OBJ_FIND_RAT_TONIC, 4
.set QUEST_OBJ_DELIVER_RAT_TONIC_TO_RON, 5
.set QUEST_OBJ_FIND_SCABBERS_LEAKY_CAULDRON, 6
.set QUEST_OBJ_FIND_CROOKSHANKS, 7
.set QUEST_OBJ_LEAVE_CELLAR_UNUSED, 8
.set QUEST_OBJ_FIND_YOUR_SEAT, 9
.set QUEST_OBJ_FIND_TREVOR, 10
.set QUEST_OBJ_BLOCK_THE_DOORS_UNUSED, 11
.set QUEST_OBJ_FIND_CHOCOLATE, 12
.set QUEST_OBJ_FIND_CONDUCTOR, 13
.set QUEST_OBJ_FIND_COMMON_ROOM, 14
.set QUEST_OBJ_GO_TO_TRANSFIGURATION, 15
.set QUEST_OBJ_FIND_MCGONAGALL, 16
.set QUEST_OBJ_GO_TO_CARE_OF_MAGICAL_CREATURES, 17
.set QUEST_OBJ_FIND_ESCAPED_BOOKS, 18
.set QUEST_OBJ_GO_TO_POTIONS, 19
.set QUEST_OBJ_FIND_POTION_INGREDIENTS, 20
.set QUEST_OBJ_RETURN_INGREDIENTS_TO_SNAPE, 21
.set QUEST_OBJ_GO_TO_STAFF_ROOM, 22
.set QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_POTIONS, 23
.set QUEST_OBJ_FIND_SCABBERS_COMMON_ROOM, 24
.set QUEST_OBJ_FIND_FAT_LADY, 25
.set QUEST_OBJ_GO_TO_DADA, 26
.set QUEST_OBJ_GO_TO_LIBRARY_FOR_DADA, 27
.set QUEST_OBJ_FIND_BOOK_PAGES, 28
.set QUEST_OBJ_RETURN_TO_DADA, 29
.set QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_DADA, 30
.set QUEST_OBJ_GO_TO_HAGRIDS_HUT_FIRST, 31
.set QUEST_OBJ_GO_TO_LIBRARY_FOR_HERMIONE, 32
.set QUEST_OBJ_FIND_HERMIONE, 33
.set QUEST_OBJ_GO_TO_GREAT_HALL, 34
.set QUEST_OBJ_GO_TO_LUPINS_OFFICE, 35
.set QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_LUPIN, 36
.set QUEST_OBJ_GO_TO_BOYS_DORMITORY, 37
.set QUEST_OBJ_GO_TO_COMMON_ROOM_LATE_UNUSED, 38
.set QUEST_OBJ_GO_TO_BOYS_DORMITORY_LATE_UNUSED, 39
.set QUEST_OBJ_GO_TO_ENTRANCE_HALL_UNUSED, 40
.set QUEST_OBJ_RETURN_TO_COMMON_ROOM_UNUSED, 41
.set QUEST_OBJ_GO_TO_BOYS_DORMITORY_FINAL_UNUSED, 42
.set QUEST_OBJ_FIND_RON_AND_HERMIONE, 43
.set QUEST_OBJ_GO_TO_HAGRIDS_HUT_SECOND, 44
.set QUEST_OBJ_GO_TO_WHOMPING_WILLOW, 45
.set QUEST_OBJ_FIND_PATH_BENEATH_WILLOW, 46
.set QUEST_OBJ_FOLLOW_PATH_TO_SHRIEKING_SHACK, 47
.set QUEST_OBJ_RETURN_TO_HOGWARTS, 48
.set QUEST_OBJ_WALK_TO_LAKE, 49
.set QUEST_OBJ_SECRET_PATH_TO_HAGRIDS_HUT, 50
.set QUEST_OBJ_GO_TO_HAGRIDS_HUT_LATE_UNUSED, 51
.set QUEST_OBJ_GO_BACK_TO_LAKE, 52
.set QUEST_OBJ_GO_TO_ROOFTOP, 53
.set QUEST_OBJ_SPEAK_TO_WEASLEYS, 54
.set QUEST_OBJ_FIND_RON, 55
.set QUEST_OBJ_RETURN_TO_LUPIN, 56
.set QUEST_OBJ_RESCUE_SIRIUS, 57
.set QUEST_OBJ_FIND_HIPPOGRIFF_BAITING_BOOK_UNUSED, 58

@ Opcode numbers; the same values as enum RoomScriptOpcode in
@ include/overworld/room_script_bytecode.h.
.set RSOP_End, 0
.set RSOP_DespawnTileActor, 1
.set RSOP_SetTileActorMoveSpeed, 2
.set RSOP_SetTileActorFlagBit, 3
.set RSOP_ClearTileActorFlagBit, 4
.set RSOP_ShowRoomDialog, 5
.set RSOP_PauseMusic, 6
.set RSOP_ResumeMusic, 7
.set RSOP_PlayMusicModuleAndFlagIfChain1, 8
.set RSOP_PlayRoomSoundEffect, 9
.set RSOP_PlaySoundById, 10
.set RSOP_SetRoomMusicVolume, 11
.set RSOP_SetSoundEffectVolume, 12
.set RSOP_DelayedRespawnRowAndRunChain, 13
.set RSOP_SetStoryStage, 14
.set RSOP_SetTileActorAnimState, 15
.set RSOP_QueueTileActorMove, 16
.set RSOP_ReturnToOverworld, 17
.set RSOP_SetAllQueuedMoveParams, 18
.set RSOP_ClearAllQueuedMoves, 19
.set RSOP_SetTileActorPosition, 20
.set RSOP_PlayCutscene, 21
.set RSOP_CloseRoomDialog, 22
.set RSOP_SetTileActorFollowTarget, 23
.set RSOP_StartTileActorRouteWalk, 24
.set RSOP_StartTileActorScript, 25
.set RSOP_PlayTileActorAnimation, 26
.set RSOP_OpenMainMenu, 27
.set RSOP_ArmChainYield, 28
.set RSOP_GotoIfQuestStateCompare, 29
.set RSOP_GotoIfQuestStatePairCompare, 30
.set RSOP_SetQuestState, 31
.set RSOP_CopyQuestState, 32
.set RSOP_StopTileActor, 33
.set RSOP_SetTileActorAnimStateWithSpeed, 34
.set RSOP_PatchRoomBackgroundTile, 35
.set RSOP_ShowChooseCharacter, 36
.set RSOP_PlayScreenTransitionOut, 37
.set RSOP_PlayScreenTransitionIn, 38
.set RSOP_RecruitPartyFollower, 39
.set RSOP_RemovePartyFollower, 40
.set RSOP_SpawnPartyFollowerAtTile, 41
.set RSOP_SetPartyLeaderCharacter, 42
.set RSOP_StartBattle, 43
.set RSOP_SetTileActorAnimStateValue, 44
.set RSOP_GrantRoomReward, 45
.set RSOP_SetBackgroundBlendLayers, 46
.set RSOP_ShowBackgroundLayer, 47
.set RSOP_HideBackgroundLayer, 48
.set RSOP_SetBackgroundPriority, 49
.set RSOP_SetCameraFollowTileActor, 50
.set RSOP_PlaySpecialSceneEffect, 51
.set RSOP_DelayedRespawnRowAndRunChainFrames, 52
.set RSOP_SetTileActorAndLinkedVisible, 53
.set RSOP_GotoIfStoryStageCompare, 54
.set RSOP_SetRandomQuestState, 55
.set RSOP_NoOp, 56
.set RSOP_SetScreenWindow, 57
.set RSOP_HideScreenWindow, 58
.set RSOP_SetTileActorFacing, 59
.set RSOP_AddQuestState, 60
.set RSOP_SubtractQuestState, 61
.set RSOP_ClearQuestStateUpperHalf, 62
.set RSOP_NoOpAlt, 63
.set RSOP_InvokeChainIfEnabled, 64
.set RSOP_GrantPartyExperience, 65
.set RSOP_SetDefeatWarpSelector, 66
.set RSOP_SetTileActorDrawLayer, 67
.set RSOP_EnterFredAndGeorgesShop, 68
.set RSOP_FullHealParty, 69
.set RSOP_RespawnRowAndRunChain, 70
.set RSOP_StartMinigame, 71
.set RSOP_DespawnRoomRowActors, 72
.set RSOP_GrantPartySpell, 73
.set RSOP_SetOverworldMonstersDisabled, 74
.set RSOP_ClearOverworldMonstersDisabled, 75
.set RSOP_StartTileActorTurnAround, 76
.set RSOP_LockTileActorSprite, 77
.set RSOP_UnlockMinigame, 78
.set RSOP_ShowRewardPickupMessage, 79
.set RSOP_ShowItemRemovedMessage, 80
.set RSOP_ShowSpellLearnedMessage, 81
.set RSOP_SetPauseMenuLocked, 82
.set RSOP_GotoIfFolioPageGroupComplete, 83
.set RSOP_ShowFolioCategoryStatusMessage, 84
.set RSOP_ShowMinigameUnlockedMessage, 85
.set RSOP_ShowPartyLevelUpMessage, 86
.set RSOP_GrantPartyLevelUps, 87
.set RSOP_StopSoundEffectChannels, 88
.set RSOP_ConsumeRoomItem, 89
.set RSOP_ResetPartyLeaderSelection, 90
.set RSOP_GotoIfAllQuestFlagsSet, 91
.set RSOP_SetPendingChainFromExitParam, 92

.macro End
    .byte RSOP_End, 0, 0, 0
.endm

@ Sets ActorFlagPendingDestroy and ActorFlagAnimFrameLoaded on room actor (group, member) and its linked actor.
.macro DespawnTileActor group, member
    .byte RSOP_DespawnTileActor, 0, 0, 0, (\group), (\member), (255), (255)
.endm

@ Sets room actor (group, member)'s move speed to `speed` pixels (x1.25 for the player) and bActionFlags bit 0x8.
.macro SetTileActorMoveSpeed group, member, speed
    .byte RSOP_SetTileActorMoveSpeed, 0, 0, 0, (\group), (\member), (((\speed) >> 0) & 0xFF), (((\speed) >> 8) & 0xFF)
.endm

.macro SetTileActorFlagBit group, member, bit
    .byte RSOP_SetTileActorFlagBit, 0, 0, 0, (\group), (\member), (\bit), (255)
.endm

.macro ClearTileActorFlagBit group, member, bit
    .byte RSOP_ClearTileActorFlagBit, 0, 0, 0, (\group), (\member), (\bit), (255)
.endm

@ Plays sound 5 (0x24 for block 0x270) and opens dialog block `blockId`. Yields.
.macro ShowRoomDialog blockId
    .byte RSOP_ShowRoomDialog, 0, 0, 0, (((\blockId) >> 0) & 0xFF), (((\blockId) >> 8) & 0xFF), (0), (0)
.endm

.macro PauseMusic
    .byte RSOP_PauseMusic, 0, 0, 0
.endm

.macro ResumeMusic
    .byte RSOP_ResumeMusic, 0, 0, 0
.endm

@ PlayMusicModule(moduleId); in chain 1 also sets GameModeFlagKeepScriptMusic.
.macro PlayMusicModuleAndFlagIfChain1 moduleId
    .byte RSOP_PlayMusicModuleAndFlagIfChain1, 0, 0, 0, (\moduleId), (255), (255), (255)
.endm

@ PlayJingle(soundId); in chain 1 also sets GameModeFlagKeepScriptMusic.
.macro PlayRoomSoundEffect soundId
    .byte RSOP_PlayRoomSoundEffect, 0, 0, 0, (\soundId), (255), (255), (255)
.endm

.macro PlaySoundById soundId
    .byte RSOP_PlaySoundById, 0, 0, 0, (\soundId), (255), (255), (255)
.endm

@ SetMusicVolume(volume, 1).
.macro SetRoomMusicVolume volume, unused0, unused1, unused2
    .byte RSOP_SetRoomMusicVolume, 0, 0, 0, (\volume), (\unused0), (\unused1), (\unused2)
.endm

.macro SetSoundEffectVolume volume, unused0, unused1, unused2
    .byte RSOP_SetSoundEffectVolume, 0, 0, 0, (\volume), (\unused0), (\unused1), (\unused2)
.endm

@ RespawnGroupAndRunChain(respawnRow, chainRow) after `delay` * 30 frames, or now if 0. Yields
@ when delayed and not the last record.
.macro DelayedRespawnRowAndRunChain delay, respawnRow, chainRow
    .byte RSOP_DelayedRespawnRowAndRunChain, 0, 0, 0, (((\delay) >> 0) & 0xFF), (((\delay) >> 8) & 0xFF), (\respawnRow), (\chainRow)
.endm

.macro SetStoryStage stage
    .byte RSOP_SetStoryStage, 0, 0, 0, (\stage), (255), (255), (255)
.endm

@ Sets room actor (group, member)'s action state to 4.
.macro SetTileActorAnimState group, member
    .byte RSOP_SetTileActorAnimState, 0, 0, 0, (\group), (\member), (255), (255)
.endm

@ Starts camera effect 1 of the current control slot toward room actor (group, member): step `speed`
@ (sign-magnitude 8.8), wCounter `unknown`, RespawnGroupAndRunChain(byte1, byte2). Saves and zeroes the
@ controlled actor's velocity. Yields.
.macro QueueTileActorMove group, member, byte1, byte2, speed, unknown
    .byte RSOP_QueueTileActorMove, 0, 0, 0, (\group), (\member), (\byte1), (\byte2), (((\speed) >> 0) & 0xFF), (((\speed) >> 8) & 0xFF), (((\unknown) >> 0) & 0xFF), (((\unknown) >> 8) & 0xFF)
.endm

@ Sets every exit parameter to `exitParam` and pushes Overworld with `exitId`.
.macro ReturnToOverworld exitId, exitParam
    .byte RSOP_ReturnToOverworld, 0, 0, 0, (\exitId), (\exitParam), (255), (255)
.endm

@ Starts camera effect 3 on every control slot: step `amplitude` pixels for `duration` * 30
@ frames (0 = forever), RespawnGroupAndRunChain(respawnRow, chainRow).
.macro SetAllQueuedMoveParams duration, amplitude, respawnRow, chainRow, unused
    .byte RSOP_SetAllQueuedMoveParams, 0, 0, 0, (((\duration) >> 0) & 0xFF), (((\duration) >> 8) & 0xFF), (((\amplitude) >> 0) & 0xFF), (((\amplitude) >> 8) & 0xFF), (\respawnRow), (\chainRow), (((\unused) >> 0) & 0xFF), (((\unused) >> 8) & 0xFF)
.endm

@ Sets every control slot's camera effect to state 0.
.macro ClearAllQueuedMoves
    .byte RSOP_ClearAllQueuedMoves, 0, 0, 0
.endm

@ Places room actor (group, member) at pixel (x, y) facing `facing`; sets bActionFlags bit 0x10.
.macro SetTileActorPosition x, y, group, member, facing, unused
    .byte RSOP_SetTileActorPosition, 0, 0, 0, (((\x) >> 0) & 0xFF), (((\x) >> 8) & 0xFF), (((\y) >> 0) & 0xFF), (((\y) >> 8) & 0xFF), (\group), (\member), (\facing), (\unused)
.endm

@ Stores the pending row and chain and pushes the cutscene mode for `cutsceneId` (see
@ RoomScriptOpPlayCutscene).
.macro PlayCutscene cutsceneId, pendingRow, pendingChain
    .byte RSOP_PlayCutscene, 0, 0, 0, (\cutsceneId), (\pendingRow), (\pendingChain), (255)
.endm

@ Sets every exit parameter to `exitParam` and clears GameModeFlagOverlayMode.
.macro CloseRoomDialog unused0, exitParam, unused1, unused2
    .byte RSOP_CloseRoomDialog, 0, 0, 0, (\unused0), (\exitParam), (\unused1), (\unused2)
.endm

@ Sets room actor (group, member) to action state 0x12 following room actor (targetGroup,
@ targetMember), or control slot 0's actor if `useTargetTile` is 0.
.macro SetTileActorFollowTarget group, member, targetGroup, targetMember, useTargetTile, resumeDistance, stopDistance, unused
    .byte RSOP_SetTileActorFollowTarget, 0, 0, 0, (\group), (\member), (\targetGroup), (\targetMember), (\useTargetTile), (\resumeDistance), (\stopDistance), (\unused)
.endm

@ Starts room actor (group, member) walking route `route` from `waypoint`: action state
@ 7 + `walkMode` (6 also clears ActorFlagHasAnimation), waiting `waitTicks` at each
@ waypoint. A walk-once route ends with RespawnGroupAndRunChain(finishRespawnRow,
@ finishChainRow). A nonzero `noPlatePress` keeps pressure plates from reacting to it. Yields.
.macro StartTileActorRouteWalk group, member, finishRespawnRow, finishChainRow, route, waypoint, walkMode, waitTicks, noPlatePress, unused0
    .byte RSOP_StartTileActorRouteWalk, 0, 0, 0, (\group), (\member), (\finishRespawnRow), (\finishChainRow), (\route), (\waypoint), (\walkMode), (\waitTicks), (\noPlatePress), (\unused0), (255), (255)
.endm

@ Starts room actor (group, member) walking to pixel (targetX, targetY) in action state 15
@ (facing halved for four-way actors). On arrival it runs RespawnGroupAndRunChain(respawnRow,
@ chainRow), or stands when both are 0. Yields.
.macro StartTileActorScript targetX, targetYLow, targetYHigh, group, member, respawnRow, chainRow, facing, unused0, unused1, unused2
    .byte RSOP_StartTileActorScript, 0, 0, 0, (((\targetX) >> 0) & 0xFF), (((\targetX) >> 8) & 0xFF), (\targetYLow), (\targetYHigh), (\group), (\member), (\respawnRow), (\chainRow), (\facing), (\unused0), (\unused1), (\unused2)
.endm

@ StartNpcScriptAnimation on room actor (group, member) with `animId`. Yields.
.macro PlayTileActorAnimation group, member, animId
    .byte RSOP_PlayTileActorAnimation, 0, 0, 0, (\group), (\member), (((\animId) >> 0) & 0xFF), (((\animId) >> 8) & 0xFF)
.endm

.macro OpenMainMenu
    .byte RSOP_OpenMainMenu, 0, 0, 0
.endm

@ Sets the run state to 1 (arm) or 0; an armed yielding opcode ends the walk.
.macro ArmChainYield arm
    .byte RSOP_ArmChainYield, 0, 0, 0, (\arm), (255), (255), (255)
.endm

.macro GotoIfQuestStateCompare index, cmpOp, value, trueChain, falseChain, trueRow, falseRow
    .byte RSOP_GotoIfQuestStateCompare, 0, 0, 0, (\index), (\cmpOp), (\value), (\trueChain), (\falseChain), (\trueRow), (\falseRow), (255)
.endm

.macro GotoIfQuestStatePairCompare indexA, cmpOp, indexB, trueChain, falseChain, trueRow, falseRow
    .byte RSOP_GotoIfQuestStatePairCompare, 0, 0, 0, (\indexA), (\cmpOp), (\indexB), (\trueChain), (\falseChain), (\trueRow), (\falseRow), (255)
.endm

.macro SetQuestState value, index
    .byte RSOP_SetQuestState, 0, 0, 0, (\value), (\index), (255), (255)
.endm

.macro CopyQuestState srcIndex, dstIndex, unused0, unused1
    .byte RSOP_CopyQuestState, 0, 0, 0, (\srcIndex), (\dstIndex), (\unused0), (\unused1)
.endm

@ Stops room actor (group, member)'s move and resets its animation counters, ends an active field spell, and sets
@ the actor's action state and the player's previous action state to 0.
.macro StopTileActor group, member
    .byte RSOP_StopTileActor, 0, 0, 0, (\group), (\member), (255), (255)
.endm

@ Sets room actor (group, member)'s action state and previous action state to 0x21 and its move speed
@ to 2.5 pixels.
.macro SetTileActorAnimStateWithSpeed group, member
    .byte RSOP_SetTileActorAnimStateWithSpeed, 0, 0, 0, (\group), (\member), (255), (255)
.endm

.macro PatchRoomBackgroundTile x, y, tileId, layer, unused
    .byte RSOP_PatchRoomBackgroundTile, 0, 0, 0, (((\x) >> 0) & 0xFF), (((\x) >> 8) & 0xFF), (((\y) >> 0) & 0xFF), (((\y) >> 8) & 0xFF), (((\tileId) >> 0) & 0xFF), (((\tileId) >> 8) & 0xFF), (\layer), (\unused)
.endm

@ Sets GameModeFlagOverlayMode and pushes ChooseCharacter with the three mode arguments. Yields.
.macro ShowChooseCharacter modeArg1, modeArg2, modeArg3, unused
    .byte RSOP_ShowChooseCharacter, 0, 0, 0, (\modeArg1), (\modeArg2), (\modeArg3), (\unused)
.endm

@ PlayScreenTransitionOutByIndex(0x3F, 2).
.macro PlayScreenTransitionOut
    .byte RSOP_PlayScreenTransitionOut, 0, 0, 0
.endm

@ PlayScreenTransitionInByIndex(0x3F, 2).
.macro PlayScreenTransitionIn
    .byte RSOP_PlayScreenTransitionIn, 0, 0, 0
.endm

@ CatchUpToHarryLevel(characterId), then spawns it as follower 0, or follower 1 if 0 exists.
.macro RecruitPartyFollower characterId
    .byte RSOP_RecruitPartyFollower, 0, 0, 0, (\characterId), (255), (255), (255)
.endm

.macro RemovePartyFollower characterId
    .byte RSOP_RemovePartyFollower, 0, 0, 0, (\characterId), (255), (255), (255)
.endm

@ Spawns `characterId`'s NPC actor, removes it from the party and registers it as room actor
@ (group, member).
.macro SpawnPartyFollowerAtTile characterId, group, member, unused
    .byte RSOP_SpawnPartyFollowerAtTile, 0, 0, 0, (\characterId), (\group), (\member), (\unused)
.endm

.macro SetPartyLeaderCharacter characterId
    .byte RSOP_SetPartyLeaderCharacter, 0, 0, 0, (\characterId), (255), (255), (255)
.endm

@ Clears the chain call stack, stores the pending row and chain, plays sound 6 and pushes Battle
@ with `battleId`.
.macro StartBattle battleId, pendingRow, pendingChain
    .byte RSOP_StartBattle, 0, 0, 0, (\battleId), (\pendingRow), (\pendingChain), (255)
.endm

@ Sets room actor (group, member)'s action state to `actionState` and its substate to 0.
.macro SetTileActorAnimStateValue group, member, actionState
    .byte RSOP_SetTileActorAnimStateValue, 0, 0, 0, (\group), (\member), (\actionState), (255)
.endm

@ PlayerReceiveReward(rewardId), or PlayerReceiveRewardAlt if `variant` is nonzero.
.macro GrantRoomReward rewardId, variant
    .byte RSOP_GrantRoomReward, 0, 0, 0, (\rewardId), (\variant), (255), (255)
.endm

@ Sets the alpha-blend first targets to the BGs whose operand is 1, second targets 0x1F.
.macro SetBackgroundBlendLayers bg0, bg1, bg2, bg3
    .byte RSOP_SetBackgroundBlendLayers, 0, 0, 0, (\bg0), (\bg1), (\bg2), (\bg3)
.endm

.macro ShowBackgroundLayer bg, unused0, unused1, unused2
    .byte RSOP_ShowBackgroundLayer, 0, 0, 0, (\bg), (\unused0), (\unused1), (\unused2)
.endm

.macro HideBackgroundLayer bg
    .byte RSOP_HideBackgroundLayer, 0, 0, 0, (\bg), (255), (255), (255)
.endm

.macro SetBackgroundPriority bg, priority, unused0, unused1
    .byte RSOP_SetBackgroundPriority, 0, 0, 0, (\bg), (\priority), (\unused0), (\unused1)
.endm

@ SetCameraFollowTarget on room actor (group, member) with an uninitialized offset.
.macro SetCameraFollowTileActor group, member, unused0, unused1
    .byte RSOP_SetCameraFollowTileActor, 0, 0, 0, (\group), (\member), (\unused0), (\unused1)
.endm

@ Runs special scene effect `mode` 0-5 (see RoomScriptOpPlaySpecialSceneEffect).
.macro PlaySpecialSceneEffect mode
    .byte RSOP_PlaySpecialSceneEffect, 0, 0, 0, (\mode), (255), (255), (255)
.endm

.macro DelayedRespawnRowAndRunChainFrames delay, respawnRow, chainRow
    .byte RSOP_DelayedRespawnRowAndRunChainFrames, 0, 0, 0, (((\delay) >> 0) & 0xFF), (((\delay) >> 8) & 0xFF), (\respawnRow), (\chainRow)
.endm

.macro SetTileActorAndLinkedVisible group, member, visible, unused
    .byte RSOP_SetTileActorAndLinkedVisible, 0, 0, 0, (\group), (\member), (\visible), (\unused)
.endm

.macro GotoIfStoryStageCompare cmpOp, value, trueChain, falseChain, trueRow, falseRow
    .byte RSOP_GotoIfStoryStageCompare, 0, 0, 0, (\cmpOp), (\value), (\trueChain), (\falseChain), (\trueRow), (\falseRow), (255), (255)
.endm

@ Sets quest state `index` to Mt19937RandRange(min, max).
.macro SetRandomQuestState min, max, index, unused0, unused1, unused2
    .byte RSOP_SetRandomQuestState, 0, 0, 0, (((\min) >> 0) & 0xFF), (((\min) >> 8) & 0xFF), (((\max) >> 0) & 0xFF), (((\max) >> 8) & 0xFF), (\index), (\unused0), (\unused1), (\unused2)
.endm

.macro NoOp unknown
    .byte RSOP_NoOp, 0, 0, 0, (((\unknown) >> 0) & 0xFF), (((\unknown) >> 8) & 0xFF), (((\unknown) >> 16) & 0xFF), (((\unknown) >> 24) & 0xFF)
.endm

.macro SetScreenWindow windowId, unused0, x0, y0, x1, y1, winIn, winOut, unused1
    .byte RSOP_SetScreenWindow, 0, 0, 0, (\windowId), (\unused0), (((\x0) >> 0) & 0xFF), (((\x0) >> 8) & 0xFF), (((\y0) >> 0) & 0xFF), (((\y0) >> 8) & 0xFF), (((\x1) >> 0) & 0xFF), (((\x1) >> 8) & 0xFF), (((\y1) >> 0) & 0xFF), (((\y1) >> 8) & 0xFF), (\winIn), (\winOut), (((\unused1) >> 0) & 0xFF), (((\unused1) >> 8) & 0xFF), (((\unused1) >> 16) & 0xFF), (((\unused1) >> 24) & 0xFF)
.endm

.macro HideScreenWindow windowId, unused0, unused1, unused2
    .byte RSOP_HideScreenWindow, 0, 0, 0, (\windowId), (\unused0), (\unused1), (\unused2)
.endm

@ Sets room actor (group, member) to action state 3 facing `facing` (halved for four-way actors).
.macro SetTileActorFacing group, member, facing
    .byte RSOP_SetTileActorFacing, 0, 0, 0, (\group), (\member), (\facing), (255)
.endm

.macro AddQuestState amount, index
    .byte RSOP_AddQuestState, 0, 0, 0, (\amount), (\index), (255), (255)
.endm

.macro SubtractQuestState amount, index
    .byte RSOP_SubtractQuestState, 0, 0, 0, (\amount), (\index), (255), (255)
.endm

@ Zeroes quest state 0x80-0xFF.
.macro ClearQuestStateUpperHalf
    .byte RSOP_ClearQuestStateUpperHalf, 0, 0, 0
.endm

.macro NoOpAlt unknown
    .byte RSOP_NoOpAlt, 0, 0, 0, (((\unknown) >> 0) & 0xFF), (((\unknown) >> 8) & 0xFF), (((\unknown) >> 16) & 0xFF), (((\unknown) >> 24) & 0xFF)
.endm

@ Jumps to `chain` without returning, and spawns row `row`'s missing actors if ShouldRunRoomIndex
@ allows it.
.macro InvokeChainIfEnabled row, chain
    .byte RSOP_InvokeChainIfEnabled, 0, 0, 0, (\row), (\chain), (255), (255)
.endm

.macro GrantPartyExperience experience, unused
    .byte RSOP_GrantPartyExperience, 0, 0, 0, (((\experience) >> 0) & 0xFF), (((\experience) >> 8) & 0xFF), (((\unused) >> 0) & 0xFF), (((\unused) >> 8) & 0xFF)
.endm

.macro SetDefeatWarpSelector value
    .byte RSOP_SetDefeatWarpSelector, 0, 0, 0, (\value), (255), (255), (255)
.endm

.macro SetTileActorDrawLayer group, member, priority, unused
    .byte RSOP_SetTileActorDrawLayer, 0, 0, 0, (\group), (\member), (\priority), (\unused)
.endm

@ Stores the pending row and chain and pushes FredAndGeorgesShop with `modeArg`.
.macro EnterFredAndGeorgesShop modeArg, pendingRow, pendingChain
    .byte RSOP_EnterFredAndGeorgesShop, 0, 0, 0, (\modeArg), (\pendingRow), (\pendingChain), (255)
.endm

@ Restores all three party members' HP and MP; QUEST_SCRATCH_RESULT is 1 if any changed.
.macro FullHealParty
    .byte RSOP_FullHealParty, 0, 0, 0
.endm

.macro RespawnRowAndRunChain respawnRow, chainRow
    .byte RSOP_RespawnRowAndRunChain, 0, 0, 0, (\respawnRow), (\chainRow), (255), (255)
.endm

@ Stores the pending row and chain and pushes minigame 0, 1, 2 or 4 (its help topic if
@ `showHelp`) with mode argument 3 = `param`.
.macro StartMinigame minigameId, param, showHelp, pendingRow, pendingChain
    .byte RSOP_StartMinigame, 0, 0, 0, (\minigameId), (\param), (\showHelp), (\pendingRow), (\pendingChain), (255), (255), (255)
.endm

@ DespawnTileActor on every actor of row `row`, if ShouldRunRoomIndex allows it.
.macro DespawnRoomRowActors row
    .byte RSOP_DespawnRoomRowActors, 0, 0, 0, (\row), (255), (255), (255)
.endm

@ Increments `characterId`'s known-spell count, up to 6 (7 for master stats slot 1).
.macro GrantPartySpell characterId
    .byte RSOP_GrantPartySpell, 0, 0, 0, (\characterId), (255), (255), (255)
.endm

.macro SetOverworldMonstersDisabled
    .byte RSOP_SetOverworldMonstersDisabled, 0, 0, 0
.endm

.macro ClearOverworldMonstersDisabled
    .byte RSOP_ClearOverworldMonstersDisabled, 0, 0, 0
.endm

@ Sets room actor (group, member) to action state 0x1B facing `facing` (halved for four-way actors)
@ and turning around every `turnInterval` ticks.
.macro StartTileActorTurnAround group, member, facing, turnInterval
    .byte RSOP_StartTileActorTurnAround, 0, 0, 0, (\group), (\member), (\facing), (\turnInterval)
.endm

@ If `set`, sets bit 0x4 of room actor (group, member)'s bTypeFlags (NPCs: keep the sprite frame).
.macro LockTileActorSprite group, member, set
    .byte RSOP_LockTileActorSprite, 0, 0, 0, (\group), (\member), (\set), (255)
.endm

@ Sets the save header's unlock flag for minigame `minigameId` (0-4).
.macro UnlockMinigame minigameId
    .byte RSOP_UnlockMinigame, 0, 0, 0, (\minigameId), (255), (255), (255)
.endm

@ Plays jingle 0x1A and opens dialog block 0x28D (0x295 above reward 0x4E) naming the reward.
@ Yields.
.macro ShowRewardPickupMessage rewardId
    .byte RSOP_ShowRewardPickupMessage, 0, 0, 0, (\rewardId), (0), (0), (255)
.endm

@ Opens dialog block 0x28E naming reward `rewardId`. Yields.
.macro ShowItemRemovedMessage rewardId
    .byte RSOP_ShowItemRemovedMessage, 0, 0, 0, (\rewardId), (0), (0), (255)
.endm

@ Plays jingle 0x1A and opens dialog block 0x28F naming spell text 0xAC2 + `spellId`; skipped
@ if `skipIfSaveFlag` and save flag 0x04 is set. Yields.
.macro ShowSpellLearnedMessage spellId, skipIfSaveFlag
    .byte RSOP_ShowSpellLearnedMessage, 0, 0, 0, (\spellId), (\skipIfSaveFlag), (0), (0)
.endm

.macro SetPauseMenuLocked locked, unused0, unused1, unused2
    .byte RSOP_SetPauseMenuLocked, 0, 0, 0, (\locked), (\unused0), (\unused1), (\unused2)
.endm

.macro GotoIfFolioPageGroupComplete pageGroupId, trueRow, trueChain, falseRow, falseChain, unused0, unused1, unused2
    .byte RSOP_GotoIfFolioPageGroupComplete, 0, 0, 0, (\pageGroupId), (\trueRow), (\trueChain), (\falseRow), (\falseChain), (\unused0), (\unused1), (\unused2)
.endm

@ Opens dialog block 0x290 (0x291 if `complete`) naming text 0x405 + `category`. Yields.
.macro ShowFolioCategoryStatusMessage category, complete
    .byte RSOP_ShowFolioCategoryStatusMessage, 0, 0, 0, (\category), (\complete), (0), (0)
.endm

@ Opens dialog block 0x292 naming text 0xA4A + `minigameId` (block 0x299 for minigame 3).
@ Yields.
.macro ShowMinigameUnlockedMessage minigameId
    .byte RSOP_ShowMinigameUnlockedMessage, 0, 0, 0, (\minigameId), (0), (0), (255)
.endm

@ Opens dialog block 0x293 with `levelCount`. Yields.
.macro ShowPartyLevelUpMessage levelCount
    .byte RSOP_ShowPartyLevelUpMessage, 0, 0, 0, (\levelCount), (0), (0), (255)
.endm

.macro GrantPartyLevelUps levelCount
    .byte RSOP_GrantPartyLevelUps, 0, 0, 0, (\levelCount), (255), (255), (255)
.endm

.macro StopSoundEffectChannels
    .byte RSOP_StopSoundEffectChannels, 0, 0, 0
.endm

.macro ConsumeRoomItem itemId
    .byte RSOP_ConsumeRoomItem, 0, 0, 0, (\itemId), (255), (255), (255)
.endm

@ CycleSelectedFieldSpell(g_pPlayerActor, 2).
.macro ResetPartyLeaderSelection
    .byte RSOP_ResetPartyLeaderSelection, 0, 0, 0
.endm

@ Branches on quest states QUEST_FOLIO_REWARD_FIRST-LAST all being nonzero.
.macro GotoIfAllQuestFlagsSet trueChain, falseChain, trueRow, falseRow
    .byte RSOP_GotoIfAllQuestFlagsSet, 0, 0, 0, (\trueChain), (\falseChain), (\trueRow), (\falseRow)
.endm

@ Jumps to `chainIfExit0` or `chainIfExit1` when the first exit parameter is 0 or 1.
.macro SetPendingChainFromExitParam chainIfExit1, chainIfExit0, unused0, unused1
    .byte RSOP_SetPendingChainFromExitParam, 0, 0, 0, (\chainIfExit1), (\chainIfExit0), (\unused0), (\unused1)
.endm
