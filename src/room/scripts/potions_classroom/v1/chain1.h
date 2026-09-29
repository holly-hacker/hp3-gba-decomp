const u8 g_abRoom01V1Chain1[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_RespawnRowAndRunChain(2, 0),
    RS_DelayedRespawnRowAndRunChainFrames(10, 0, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
