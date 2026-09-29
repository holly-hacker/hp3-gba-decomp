const u8 g_abRoom15V1Chain9[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(15, 0, 0, 0, 15, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(15, 0, 0, 0, 1000, 0),
    RS_End(),
};
