const u8 g_abRoom07V2Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 227),
    RS_SetQuestState(1, 226),
    RS_QueueTileObjectMove(1, 0, 0, 0, 1700, 0),
    // "A bar of chocolate, please."
    // "There you are, my dear. That'll be one Sickle."
    // "Thanks."
    RS_ShowRoomDialog(136),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1500, 0),
    RS_DelayedRespawnRowAndRunChain(0, 3, 0),
    RS_DespawnTileObject(2, 0),
    RS_DespawnTileObject(2, 1),
    RS_SetQuestState(1, 246),
    RS_DespawnTileObject(2, 2),
    RS_SetQuestState(6, 6),
    RS_SetQuestState(56, 25),
    RS_GrantRoomReward(76, 0),
#ifdef VERSION_JP
    RS_ShowRewardPickupMessage(76),
#endif
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
