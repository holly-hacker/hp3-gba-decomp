const u8 g_abRoom45V1Chain73[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChainFrames(0, 5, 0),
    RS_StartTileObjectScript(588, 27, 2, 5, 0, 0, 0, 6, 255, 255, 255),
    RS_SetTileObjectFacing(5, 0, 6),
    RS_StartTileObjectScript(573, 27, 2, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_SetTileObjectFacing(0, 255, 2),
    // "Any luck?"
    // "No. You?"
    // "I'm afraid not. They must have gone this way."
    RS_ShowRoomDialog(562),
    RS_StartTileObjectScript(573, 27, 2, 5, 0, 0, 0, 2, 255, 255, 255),
    RS_DespawnTileObject(5, 0),
    RS_RecruitPartyFollower(5),
    RS_SetTileObjectFacing(0, 255, 4),
    RS_DelayedRespawnRowAndRunChainFrames(0, 0, 16),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
