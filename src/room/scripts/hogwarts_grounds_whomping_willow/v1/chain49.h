const u8 g_abRoom15V1Chain49[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "There's Hagrid! Don't let him see us!"
    RS_ShowRoomDialog(590),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(23, 0, 0, 75, 400, 0),
    RS_End(),
};
