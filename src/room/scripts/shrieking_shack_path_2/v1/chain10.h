const u8 g_abRoom45V1Chain10[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_QueueTileObjectMove(0, 1, 0, 0, 1610, 0),
    RS_DelayedRespawnRowAndRunChainFrames(48, 0, 0),
    RS_DelayedRespawnRowAndRunChain(0, 0, 2),
    RS_DelayedRespawnRowAndRunChain(11, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1800, 0),
    RS_GotoIfQuestStateCompare(236, 0, 0, 69, 0, 0, 0),
    RS_SetQuestState(1, 232),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
