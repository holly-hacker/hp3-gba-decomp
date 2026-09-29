const u8 g_abRoom42V3Chain5[] = {
    RS_ArmChainYield(0),
    RS_Unk02(3, 1, 3),
    RS_Unk02(1, 1, 3),
    RS_StartObjectAnimSequence(1, 1, 0, 0, 6, 2, 1, 0, 0, 0),
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(1, 1, 0, 0, 1200, 0),
    RS_DelayedRespawnRowAndRunChainFrames(0, 0, 14),
    RS_End(),
};
