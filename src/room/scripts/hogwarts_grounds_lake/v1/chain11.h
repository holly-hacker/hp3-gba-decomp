const u8 g_abRoom13V1Chain11[] = {
    RS_ArmChainYield(1),
    // "Look, it's us... and Lupin's closing in!"
    RS_ShowRoomDialog(595),
    RS_QueueTileObjectMove(8, 1, 0, 0, 2000, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(8, 0, 0, 0, 10, 0, 1, 0, 0, 0),
    RS_End(),
};
