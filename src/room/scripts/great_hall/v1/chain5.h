const u8 g_abRoom17V1Chain5[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(2, 14, 0, 0, 1600, 0),
    RS_RemovePartyFollower(7),
    RS_RespawnRowAndRunChain(4, 0),
    RS_RespawnRowAndRunChain(3, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 14, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_End(),
};
