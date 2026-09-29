const u8 g_abRoom39V1Chain33[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectFacing(0, 255, 6),
    RS_QueueTileObjectMove(2, 0, 0, 0, 1200, 0),
    RS_PlayTileObjectAnimation(2, 0, 4),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlayTileObjectAnimation(2, 0, 4),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetTileObjectFacing(2, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    // "Thanks!"
    RS_ShowRoomDialog(85),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
