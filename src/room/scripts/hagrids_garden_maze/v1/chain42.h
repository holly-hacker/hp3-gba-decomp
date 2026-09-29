const u8 g_abRoom12V1Chain42[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetPauseMenuLocked(1, 255, 255, 255),
    RS_ClearTileObjectFlagBit(0, 255, 2),
    RS_RespawnRowAndRunChain(0, 32),
    RS_End(),
};
