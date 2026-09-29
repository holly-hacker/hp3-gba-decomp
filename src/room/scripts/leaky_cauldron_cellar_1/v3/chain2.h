const u8 g_abRoom38V3Chain2[] = {
    RS_DespawnTileObject(4, 0),
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
