const u8 g_abRoom42V3Chain3[] = {
    RS_ArmChainYield(0),
    RS_Unk02(1, 1, 2),
    RS_Unk02(1, 0, 2),
    RS_StartTileObjectScript(523, 140, 1, 1, 1, 0, 0, 4, 255, 255, 255),
    RS_StartObjectAnimSequence(1, 0, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChainFrames(30, 0, 10),
    RS_End(),
};
