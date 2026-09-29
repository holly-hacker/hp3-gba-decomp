const u8 g_abRoom19V1Chain4[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DespawnTileObject(2, 0),
    RS_DespawnTileObject(2, 2),
    RS_DespawnTileObject(2, 1),
    RS_QueueTileObjectMove(2, 5, 0, 0, 1200, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "The lady is found!"
    RS_ShowRoomDialog(390),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_InvokeChainIfEnabled(0, 6),
    RS_End(),
};
