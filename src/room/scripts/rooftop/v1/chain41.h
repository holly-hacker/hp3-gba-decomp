const u8 g_abRoom25V1Chain41[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 19, 0),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_QueueTileObjectMove(19, 0, 0, 0, 1200, 0),
    RS_StartObjectAnimSequence(19, 0, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
