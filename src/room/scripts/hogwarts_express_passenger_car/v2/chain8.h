const u8 g_abRoom06V2Chain8[] = {
    RS_DelayedRespawnRowAndRunChain(0, 5, 0),
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(187, 126, 0, 0, 255, 0, 0, 5, 255, 255, 255),
    RS_StartTileObjectScript(182, 232, 0, 0, 255, 0, 0, 4, 255, 255, 255),
    RS_End(),
};
