const u8 g_abRoom15V1Chain56[] = {
    RS_ArmChainYield(1),
    RS_Unk02(10, 1, 1),
    RS_PlayTileObjectAnimation(10, 1, 16),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_InvokeChainIfEnabled(0, 29),
    RS_End(),
};
