const u8 g_abRoom12V1Chain36[] = {
    RS_SetPauseMenuLocked(1, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChainFrames(1, 10, 0),
    RS_ArmChainYield(1),
    RS_ArmChainYield(0),
    RS_End(),
};
