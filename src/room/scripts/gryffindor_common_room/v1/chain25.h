const u8 g_abRoom29V1Chain25[] = {
    RS_ArmChainYield(1),
    // "LOOK!"
    // "N-no..."
    // "LONG, GINGER CAT HAIRS!"
    RS_ShowRoomDialog(497),
    // "Let's go to the Quidditch pitch. The walk and the fresh air will clear our heads..."
    RS_ShowRoomDialog(499),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1400, 0),
    RS_StartObjectAnimSequence(10, 3, 0, 0, 65, 0, 1, 0, 0, 0),
    RS_End(),
};
