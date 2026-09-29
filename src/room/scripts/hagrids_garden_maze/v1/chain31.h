const u8 g_abRoom12V1Chain31[] = {
    RS_ArmChainYield(1),
    RS_GotoIfQuestStateCompare(233, 0, 0, 28, 0, 0, 0),
    RS_SetQuestState(23, 233),
    RS_DelayedRespawnRowAndRunChainFrames(7, 0, 25),
    RS_End(),
};
