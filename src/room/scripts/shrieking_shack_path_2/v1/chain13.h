const u8 g_abRoom45V1Chain13[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectAnimState(1, 8),
    RS_SetTileObjectAnimState(1, 7),
    RS_SetQuestState(2, 231),
    RS_SetQuestState(2, 224),
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(611, 27, 2, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_SetTileObjectFacing(0, 255, 6),
    RS_ArmChainYield(0),
    RS_DelayedRespawnRowAndRunChain(0, 6, 0),
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(6, 0, 0, 0, 1200, 0),
    RS_StartObjectAnimSequence(6, 0, 0, 33, 1, 0, 1, 0, 0, 0),
    // "Any luck?"
    // "No. You?"
    // "I'm afraid not. They must have gone this way."
    RS_ShowRoomDialog(562),
    RS_StartTileObjectScript(611, 27, 2, 6, 0, 0, 0, 4, 255, 255, 255),
    RS_DespawnTileObject(21, 0),
    RS_DespawnTileObject(6, 0),
    RS_RecruitPartyFollower(6),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1600, 0),
    RS_SetTileObjectFacing(0, 255, 4),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
