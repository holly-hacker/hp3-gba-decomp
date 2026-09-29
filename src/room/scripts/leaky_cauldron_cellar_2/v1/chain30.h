const u8 g_abRoom39V1Chain30[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_QueueTileObjectMove(3, 0, 0, 0, 1200, 0),
    // "Thanks!"
    RS_ShowRoomDialog(85),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_End(),
};
