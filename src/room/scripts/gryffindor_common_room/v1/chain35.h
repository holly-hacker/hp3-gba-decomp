const u8 g_abRoom29V1Chain35[] = {
    RS_ArmChainYield(1),
    // "Professor McGonagall, Sir Cadogan has just informed me that he let a man into Gryffindor Tower!"
    // "But - but the password?"
    // "Apparently, this man already had them! He read them off a piece of paper!"
    // "Which abysmally foolish person wrote down the password and left it lying around?"
    RS_ShowRoomDialog(509),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(13, 3, 0, 0, 1000, 0),
    RS_StartObjectAnimSequence(13, 3, 0, 0, 36, 0, 1, 0, 0, 0),
    RS_End(),
};
