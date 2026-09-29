const u8 g_abRoom13V1Chain10[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 130),
    RS_SetQuestState(2, 129),
    RS_RespawnRowAndRunChain(13, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_End(),
};
