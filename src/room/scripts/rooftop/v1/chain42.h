const u8 g_abRoom25V1Chain42[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 18, 0),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_QueueTileObjectMove(18, 0, 0, 0, 1200, 0),
    RS_StartObjectAnimSequence(18, 0, 0, 0, 10, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
