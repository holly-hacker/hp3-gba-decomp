const u8 g_abRoom05V1Chain22[] = {
    RS_ArmChainYield(1),
    // "That's done it! But, what about the other door?"
    RS_ShowRoomDialog(155),
    RS_DelayedRespawnRowAndRunChain(0, 11, 0),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_SetTileObjectAnimState(11, 0),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_DelayedRespawnRowAndRunChain(0, 10, 0),
    RS_SetTileObjectAnimState(10, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 10),
    RS_End(),
};
