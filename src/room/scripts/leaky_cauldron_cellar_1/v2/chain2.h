const u8 g_abRoom38V2Chain2[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(1, 12, 0, 0, 5000, 0),
    // "C'mon you lot! We need to leave for King's Cross station right away if we want to catch the Hogwarts Express!"
    RS_ShowRoomDialog(122),
    RS_QueueTileObjectMove(0, 255, 0, 0, 5000, 0),
    RS_ArmChainYield(0),
    RS_End(),
};
