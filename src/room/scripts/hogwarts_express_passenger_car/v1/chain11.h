const u8 g_abRoom06V1Chain11[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(10, 0, 6),
    RS_StartTileObjectScript(175, 239, 0, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_StartTileObjectScript(195, 239, 0, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_End(),
};
