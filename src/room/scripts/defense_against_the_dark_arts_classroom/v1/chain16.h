const u8 g_abRoom00V1Chain16[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(9, 0, 2),
    // "Hermione, how did you write that up so quickly?"
    // "Umm... like I said, I'd read the book before. See you later..."
    RS_ShowRoomDialog(426),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(9, 0, 0, 0, 13, 0, 1, 0, 0, 0),
    RS_End(),
};
