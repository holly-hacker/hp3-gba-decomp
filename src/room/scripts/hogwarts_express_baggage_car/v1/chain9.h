const u8 g_abRoom05V1Chain9[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetTileObjectAnimState(0, 9),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DelayedRespawnRowAndRunChain(4, 0, 0),
    RS_SetTileObjectAnimState(0, 9),
    RS_DelayedRespawnRowAndRunChain(3, 0, 0),
    RS_GotoIfQuestStateCompare(249, 0, 1, 12, 13, 0, 0),
    RS_End(),
};
