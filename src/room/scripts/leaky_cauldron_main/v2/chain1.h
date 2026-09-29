const u8 g_abRoom42V2Chain1[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetQuestState(4, 25),
    RS_DelayedRespawnRowAndRunChainFrames(0, 5, 0),
    RS_SetTileObjectFlagBit(0, 255, 9),
    RS_SetStoryStage(3),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_InvokeChainIfEnabled(0, 10),
    RS_End(),
};
