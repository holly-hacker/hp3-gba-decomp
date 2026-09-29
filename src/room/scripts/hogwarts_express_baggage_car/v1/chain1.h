const u8 g_abRoom05V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(0, 7),
    RS_DespawnTileObject(0, 9),
    RS_DelayedRespawnRowAndRunChain(0, 2, 0),
    RS_SetTileObjectAnimState(2, 0),
    RS_DelayedRespawnRowAndRunChain(0, 0, 12),
    RS_End(),
};
