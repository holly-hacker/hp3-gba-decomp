#pragma once

#include "types.h"
#include "overworld/room_script.h"

// cmpOp values for CompareAndBranchRoomScript (commands_inline.h).
enum {
    RoomScriptCompareEqual,
    RoomScriptCompareNotEqual,
    RoomScriptCompareGreater,
    RoomScriptCompareGreaterEqual,
    RoomScriptCompareLess,
    RoomScriptCompareLessEqual
};

extern void CompareAndBranchRoomScript(u8 lhs, u32 cmpOp, u8 rhs, u8 trueChain, u8 falseChain, u8 trueRow,
                                       u8 falseRow);

extern const RoomScriptOpcodeHandler g_apRoomScriptOpcodeHandlers[93];  // ROM 0x0805BA8C

// Room-script opcode handlers, indexed by g_apRoomScriptOpcodeHandlers.
struct DespawnTileActorRecord;
void RoomScriptOpDespawnTileActor(struct DespawnTileActorRecord *pRecord);
struct SetTileActorMoveSpeedRecord;
void RoomScriptOpSetTileActorMoveSpeed(struct SetTileActorMoveSpeedRecord *pRecord);
struct SetTileActorFlagBitRecord;
void RoomScriptOpSetTileActorFlagBit(struct SetTileActorFlagBitRecord *pRecord);
struct ClearTileActorFlagBitRecord;
void RoomScriptOpClearTileActorFlagBit(struct ClearTileActorFlagBitRecord *pRecord);
struct ShowRoomDialogRecord;
void RoomScriptOpShowRoomDialog(struct ShowRoomDialogRecord *pRecord);
void RoomScriptOpPauseMusic(RoomScriptRecord *pRecord);
void RoomScriptOpResumeMusic(RoomScriptRecord *pRecord);
struct PlayMusicModuleAndFlagIfChain1Record;
void RoomScriptOpPlayMusicModuleAndFlagIfChain1(struct PlayMusicModuleAndFlagIfChain1Record *pRecord);
struct PlayRoomSoundEffectRecord;
void RoomScriptOpPlayRoomSoundEffect(struct PlayRoomSoundEffectRecord *pRecord);
struct PlaySoundByIdRecord;
void RoomScriptOpPlaySoundById(struct PlaySoundByIdRecord *pRecord);
struct SetRoomMusicVolumeRecord;
void RoomScriptOpSetRoomMusicVolume(struct SetRoomMusicVolumeRecord *pRecord);
struct SetSoundEffectVolumeRecord;
void RoomScriptOpSetSoundEffectVolume(struct SetSoundEffectVolumeRecord *pRecord);
struct DelayedRespawnRowAndRunChainRecord;
void RoomScriptOpDelayedRespawnRowAndRunChain(struct DelayedRespawnRowAndRunChainRecord *pRecord);
struct SetStoryStageRecord;
void RoomScriptOpSetStoryStage(struct SetStoryStageRecord *pRecord);
struct SetTileActorAnimStateRecord;
void RoomScriptOpSetTileActorAnimState(struct SetTileActorAnimStateRecord *pRecord);
struct QueueTileActorMoveRecord;
void RoomScriptOpQueueTileActorMove(struct QueueTileActorMoveRecord *pRecord);
struct ReturnToOverworldRecord;
void RoomScriptOpReturnToOverworld(struct ReturnToOverworldRecord *pRecord);
struct SetAllQueuedMoveParamsRecord;
void RoomScriptOpSetAllQueuedMoveParams(struct SetAllQueuedMoveParamsRecord *pRecord);
void RoomScriptOpClearAllQueuedMoves(RoomScriptRecord *pRecord);
struct SetTileActorPositionRecord;
void RoomScriptOpSetTileActorPosition(struct SetTileActorPositionRecord *pRecord);
struct PlayCutsceneRecord;
void RoomScriptOpPlayCutscene(struct PlayCutsceneRecord *pRecord);
struct CloseRoomDialogRecord;
void RoomScriptOpCloseRoomDialog(struct CloseRoomDialogRecord *pRecord);
struct SetTileActorFollowTargetRecord;
void RoomScriptOpSetTileActorFollowTarget(struct SetTileActorFollowTargetRecord *pRecord);
struct StartActorAnimSequenceRecord;
void RoomScriptOpStartActorAnimSequence(struct StartActorAnimSequenceRecord *pRecord);
struct StartTileActorScriptRecord;
void RoomScriptOpStartTileActorScript(struct StartTileActorScriptRecord *pRecord);
struct PlayTileActorAnimationRecord;
void RoomScriptOpPlayTileActorAnimation(struct PlayTileActorAnimationRecord *pRecord);
void RoomScriptOpOpenMainMenu(RoomScriptRecord *pRecord);
struct ArmChainYieldRecord;
void RoomScriptOpArmChainYield(struct ArmChainYieldRecord *pRecord);
struct GotoIfQuestStateCompareRecord;
void RoomScriptOpGotoIfQuestStateCompare(struct GotoIfQuestStateCompareRecord *pRecord);
struct GotoIfQuestStatePairCompareRecord;
void RoomScriptOpGotoIfQuestStatePairCompare(struct GotoIfQuestStatePairCompareRecord *pRecord);
struct SetQuestStateRecord;
void RoomScriptOpSetQuestState(struct SetQuestStateRecord *pRecord);
struct CopyQuestStateRecord;
void RoomScriptOpCopyQuestState(struct CopyQuestStateRecord *pRecord);
struct CancelActorAnimSequenceRecord;
void RoomScriptOpCancelActorAnimSequence(struct CancelActorAnimSequenceRecord *pRecord);
struct SetTileActorAnimStateWithSpeedRecord;
void RoomScriptOpSetTileActorAnimStateWithSpeed(struct SetTileActorAnimStateWithSpeedRecord *pRecord);
struct PatchRoomBackgroundTileRecord;
void RoomScriptOpPatchRoomBackgroundTile(struct PatchRoomBackgroundTileRecord *pRecord);
struct ShowChooseCharacterRecord;
void RoomScriptOpShowChooseCharacter(struct ShowChooseCharacterRecord *pRecord);
void RoomScriptOpPlayScreenTransitionOut(RoomScriptRecord *pRecord);
void RoomScriptOpPlayScreenTransitionIn(RoomScriptRecord *pRecord);
struct RecruitPartyFollowerRecord;
void RoomScriptOpRecruitPartyFollower(struct RecruitPartyFollowerRecord *pRecord);
struct RemovePartyFollowerRecord;
void RoomScriptOpRemovePartyFollower(struct RemovePartyFollowerRecord *pRecord);
struct SpawnPartyFollowerAtTileRecord;
void RoomScriptOpSpawnPartyFollowerAtTile(struct SpawnPartyFollowerAtTileRecord *pRecord);
struct Op42Record;
void RoomScriptOp42(struct Op42Record *pRecord);
struct StartBattleRecord;
void RoomScriptOpStartBattle(struct StartBattleRecord *pRecord);
struct SetTileActorAnimStateValueRecord;
void RoomScriptOpSetTileActorAnimStateValue(struct SetTileActorAnimStateValueRecord *pRecord);
struct GrantRoomRewardRecord;
void RoomScriptOpGrantRoomReward(struct GrantRoomRewardRecord *pRecord);
struct SetBackgroundBlendLayersRecord;
void RoomScriptOpSetBackgroundBlendLayers(struct SetBackgroundBlendLayersRecord *pRecord);
struct ShowBackgroundLayerRecord;
void RoomScriptOpShowBackgroundLayer(struct ShowBackgroundLayerRecord *pRecord);
struct HideBackgroundLayerRecord;
void RoomScriptOpHideBackgroundLayer(struct HideBackgroundLayerRecord *pRecord);
struct SetBackgroundPriorityRecord;
void RoomScriptOpSetBackgroundPriority(struct SetBackgroundPriorityRecord *pRecord);
struct SetCameraFollowTileActorRecord;
void RoomScriptOpSetCameraFollowTileActor(struct SetCameraFollowTileActorRecord *pRecord);
struct SpecialSceneEffectRecord;
void RoomScriptOpPlaySpecialSceneEffect(struct SpecialSceneEffectRecord *pRecord);
struct DelayedRespawnRowAndRunChainFramesRecord;
void RoomScriptOpDelayedRespawnRowAndRunChainFrames(struct DelayedRespawnRowAndRunChainFramesRecord *pRecord);
struct SetTileActorAndLinkedVisibleRecord;
void RoomScriptOpSetTileActorAndLinkedVisible(struct SetTileActorAndLinkedVisibleRecord *pRecord);
struct GotoIfStoryStageCompareRecord;
void RoomScriptOpGotoIfStoryStageCompare(struct GotoIfStoryStageCompareRecord *pRecord);
struct SetRandomQuestStateRecord;
void RoomScriptOpSetRandomQuestState(struct SetRandomQuestStateRecord *pRecord);
void RoomScriptOpNoOp(RoomScriptRecord *pRecord);
struct SetScreenWindowRecord;
void RoomScriptOpSetScreenWindow(struct SetScreenWindowRecord *pRecord);
struct HideScreenWindowRecord;
void RoomScriptOpHideScreenWindow(struct HideScreenWindowRecord *pRecord);
struct SetTileActorFacingRecord;
void RoomScriptOpSetTileActorFacing(struct SetTileActorFacingRecord *pRecord);
struct AddQuestStateRecord;
void RoomScriptOpAddQuestState(struct AddQuestStateRecord *pRecord);
struct SubtractQuestStateRecord;
void RoomScriptOpSubtractQuestState(struct SubtractQuestStateRecord *pRecord);
void RoomScriptOpClearQuestStateUpperHalf(RoomScriptRecord *pRecord);
void RoomScriptOpNoOpAlt(RoomScriptRecord *pRecord);
struct InvokeChainIfEnabledRecord;
void RoomScriptOpInvokeChainIfEnabled(struct InvokeChainIfEnabledRecord *pRecord);
struct GrantPartyExperienceRecord;
void RoomScriptOpGrantPartyExperience(struct GrantPartyExperienceRecord *pRecord);
struct SetDefeatWarpSelectorRecord;
void RoomScriptOpSetDefeatWarpSelector(struct SetDefeatWarpSelectorRecord *pRecord);
struct SetTileActorDrawLayerRecord;
void RoomScriptOpSetTileActorDrawLayer(struct SetTileActorDrawLayerRecord *pRecord);
struct EnterFredAndGeorgesShopRecord;
void RoomScriptOpEnterFredAndGeorgesShop(struct EnterFredAndGeorgesShopRecord *pRecord);
extern void RoomScriptOpFullHealParty(RoomScriptRecord *pRecord);
struct RespawnRowAndRunChainRecord;
void RoomScriptOpRespawnRowAndRunChain(struct RespawnRowAndRunChainRecord *pRecord);
struct StartMinigameRecord;
void RoomScriptOpStartMinigame(struct StartMinigameRecord *pRecord);
struct DespawnRoomRowActorsRecord;
void RoomScriptOpDespawnRoomRowActors(struct DespawnRoomRowActorsRecord *pRecord);
struct GrantPartySpellRecord;
void RoomScriptOpGrantPartySpell(struct GrantPartySpellRecord *pRecord);
void RoomScriptOpSetOverworldMonstersDisabled(RoomScriptRecord *pRecord);
void RoomScriptOpClearOverworldMonstersDisabled(RoomScriptRecord *pRecord);
struct SetTileActorFacingAndScriptPageRecord;
void RoomScriptOpSetTileActorFacingAndScriptPage(struct SetTileActorFacingAndScriptPageRecord *pRecord);
struct SetTileActorSpecialFlagRecord;
void RoomScriptOpSetTileActorSpecialFlag(struct SetTileActorSpecialFlagRecord *pRecord);
struct UnlockMinigameRecord;
void RoomScriptOpUnlockMinigame(struct UnlockMinigameRecord *pRecord);
struct ShowRewardPickupMessageRecord;
void RoomScriptOpShowRewardPickupMessage(struct ShowRewardPickupMessageRecord *pRecord);
struct ShowItemRemovedMessageRecord;
void RoomScriptOpShowItemRemovedMessage(struct ShowItemRemovedMessageRecord *pRecord);
struct ShowSpellLearnedMessageRecord;
void RoomScriptOpShowSpellLearnedMessage(struct ShowSpellLearnedMessageRecord *pRecord);
struct SetPauseMenuLockedRecord;
void RoomScriptOpSetPauseMenuLocked(struct SetPauseMenuLockedRecord *pRecord);
struct GotoIfFolioPageGroupCompleteRecord;
void RoomScriptOpGotoIfFolioPageGroupComplete(struct GotoIfFolioPageGroupCompleteRecord *pRecord);
struct ShowFolioCategoryStatusMessageRecord;
void RoomScriptOpShowFolioCategoryStatusMessage(struct ShowFolioCategoryStatusMessageRecord *pRecord);
struct ShowMinigameUnlockedMessageRecord;
void RoomScriptOpShowMinigameUnlockedMessage(struct ShowMinigameUnlockedMessageRecord *pRecord);
struct ShowPartyLevelUpMessageRecord;
void RoomScriptOpShowPartyLevelUpMessage(struct ShowPartyLevelUpMessageRecord *pRecord);
struct GrantPartyLevelUpsRecord;
void RoomScriptOpGrantPartyLevelUps(struct GrantPartyLevelUpsRecord *pRecord);
void RoomScriptOpUnmuteAllMusicChannels(RoomScriptRecord *pRecord);
struct ConsumeRoomItemRecord;
void RoomScriptOpConsumeRoomItem(struct ConsumeRoomItemRecord *pRecord);
void RoomScriptOpResetPartyLeaderSelection(RoomScriptRecord *pRecord);
struct GotoIfAllQuestFlagsSetRecord;
void RoomScriptOpGotoIfAllQuestFlagsSet(struct GotoIfAllQuestFlagsSetRecord *pRecord);
struct SetPendingChainFromExitParamRecord;
void RoomScriptOpSetPendingChainFromExitParam(struct SetPendingChainFromExitParamRecord *pRecord);
