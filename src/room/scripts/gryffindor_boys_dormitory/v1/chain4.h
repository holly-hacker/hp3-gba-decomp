const u8 g_abRoom28V1Chain4[] = {
    RS_ArmChainYield(1),
    // "Don't go without me!"
    RS_ShowRoomDialog(507),
    RS_Unk02(0, 0, 2),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(6, 1, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_End(),
};
