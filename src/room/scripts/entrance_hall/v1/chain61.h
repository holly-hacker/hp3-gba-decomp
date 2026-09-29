const u8 g_abRoom16V1Chain61[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(16, 0, 6),
    RS_SetTileObjectFacing(16, 1, 6),
    // "Hey, Potter, better watch out, the Dementors are coming!"
    // "Shove off, Malfoy."
    // "Leave him, Ron, he's not worth it. Let's get to the Gryffindor common room."
    RS_ShowRoomDialog(183),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(16, 0, 0, 0, 15, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(16, 1, 0, 0, 14, 0, 1, 0, 0, 0),
    RS_End(),
};
