const u8 g_abRoom05V1Chain7[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DelayedRespawnRowAndRunChain(3, 0, 0),
    RS_SetTileObjectAnimState(0, 8),
    RS_GotoIfQuestStateCompare(128, 0, 1, 7, 0, 0, 0),
    RS_DelayedRespawnRowAndRunChain(5, 0, 0),
    RS_SetTileObjectAnimState(0, 8),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_GotoIfQuestStateCompare(128, 0, 1, 7, 5, 0, 0),
    RS_End(),
};
