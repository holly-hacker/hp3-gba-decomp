const u8 g_abRoom17V1Chain8[] = {
    RS_ArmChainYield(1),
    // "I was wondering, Harry, if you'd like to begin the Anti-Dementor lessons I promised you?"
    // "Of course, Professor."
    // "Very well, then. Meet me in my office on the third floor."
    RS_ShowRoomDialog(483),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 15, 0, 0, 5, 0, 1, 0, 0, 0),
    RS_End(),
};
