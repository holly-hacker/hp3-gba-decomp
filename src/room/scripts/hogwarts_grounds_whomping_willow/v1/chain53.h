const u8 g_abRoom15V1Chain53[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(23, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "Hello, Buckbeak, remember me? We're going to take you for a walk."
    // "Let's hurry on to the lake!"
    RS_ShowRoomDialog(594),
    RS_SetQuestState(52, 25),
    RS_SetStoryStage(26),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
