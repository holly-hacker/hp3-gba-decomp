const u8 g_abRoom15V1Chain46[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "That took care of that - now let's get Ron!"
    RS_ShowRoomDialog(559),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetQuestState(47, 25),
    RS_ClearQuestStateUpperHalf(),
    RS_ReturnToOverworld(44, 0),
    RS_End(),
};
