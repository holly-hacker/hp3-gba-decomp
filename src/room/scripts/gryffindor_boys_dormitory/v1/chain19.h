const u8 g_abRoom28V1Chain19[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectFacing(0, 255, 4),
    // "It's a black dog!"
    RS_ShowRoomDialog(529),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 10, 0, 1, 0, 0, 0),
    RS_End(),
};
