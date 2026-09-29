const u8 g_abRoom42V2Chain4[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ClearTileObjectFlagBit(0, 255, 9),
    RS_StartTileObjectScript(548, 166, 1, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 1, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_End(),
};
