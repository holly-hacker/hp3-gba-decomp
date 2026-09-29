const u8 g_abRoom06V1Chain28[] = {
    RS_SetTileObjectFacing(3, 1, 6),
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(1, 0, 0, 0, 1100, 0),
    // "These look like the only empty seats."
    // "Who d'you reckon he is?"
    // "Professor R. J. Lupin. He's the new Defense Against the Dark Arts teacher."
    // "Zzzzzz¸"
    RS_ShowRoomDialog(109),
    RS_QueueTileObjectMove(0, 255, 9, 0, 1500, 0),
    RS_InvokeChainIfEnabled(0, 8),
    RS_End(),
};
