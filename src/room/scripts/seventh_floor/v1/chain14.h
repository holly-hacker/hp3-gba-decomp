const u8 g_abRoom24V1Chain14[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(4, 2),
    RS_DespawnTileObject(4, 0),
    RS_DespawnTileObject(4, 1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
