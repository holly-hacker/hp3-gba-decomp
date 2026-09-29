const u8 g_abRoom42V3Chain14[] = {
    RS_ArmChainYield(1),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_SetTileObjectFacing(2, 1, 6),
    RS_SetTileObjectFacing(2, 0, 6),
    // "I couldn't help hearing. Sorry..."
    // "That's not the way I'd have chosen for you to find out."
    // "No - honestly, it's OK. At least I now know what's going on."
    // "Harry, you must be very scared."
    // "I'm not. Really. Sirius Black can't be worse than Voldemort, can he?"
    // "Listen, I want you to give me your word - swear to me that you won't go looking for Black."
    RS_ShowRoomDialog(42),
    RS_ArmChainYield(0),
    RS_DelayedRespawnRowAndRunChainFrames(14, 0, 16),
    RS_StartObjectAnimSequence(2, 1, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_DelayedRespawnRowAndRunChain(6, 4, 0),
    RS_End(),
};
