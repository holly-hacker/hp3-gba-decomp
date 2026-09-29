const u8 g_abRoom29V1Chain6[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 600, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "I hope she isn't in trouble."
    RS_ShowRoomDialog(185),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_End(),
};
