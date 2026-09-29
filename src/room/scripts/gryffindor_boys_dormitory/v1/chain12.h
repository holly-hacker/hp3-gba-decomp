const u8 g_abRoom28V1Chain12[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "I'm exhausted, but I can't sleep... there's too much going on in my head..."
    RS_ShowRoomDialog(526),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_End(),
};
