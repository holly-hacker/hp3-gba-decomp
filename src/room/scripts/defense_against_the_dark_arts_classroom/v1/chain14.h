const u8 g_abRoom00V1Chain14[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(9, 0),
    // "Here it is, Professor!"
    RS_ShowRoomDialog(424),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_QueueTileObjectMove(9, 0, 0, 0, 1600, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_RemovePartyFollower(7),
    RS_RespawnRowAndRunChain(11, 0),
    RS_Unk02(9, 0, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(9, 0, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 16, 0, 1, 0, 0, 0),
    RS_End(),
};
