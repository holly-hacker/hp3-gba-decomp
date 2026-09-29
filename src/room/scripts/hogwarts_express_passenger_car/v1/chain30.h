const u8 g_abRoom06V1Chain30[] = {
    RS_SetTileObjectFacing(3, 1, 2),
    RS_ArmChainYield(1),
    // "Harry, I can't find my toad, Trevor. Can you help me find him?"
    // "Where did you last see him?"
    // "Someone said they saw him near the baggage car - but I don't think we're allowed in there."
    // "Don't worry, Neville, we'll find him for you."
    // "Thanks, Harry. I'll wait here for you."
    RS_ShowRoomDialog(143),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_SetTileObjectFacing(3, 0, 2),
    RS_StartObjectAnimSequence(3, 1, 0, 0, 6, 0, 1, 0, 0, 0),
    RS_End(),
};
