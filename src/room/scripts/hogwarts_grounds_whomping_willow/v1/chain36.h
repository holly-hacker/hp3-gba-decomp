const u8 g_abRoom15V1Chain36[] = {
    RS_ArmChainYield(1),
    // "Wow! That was great!"
    // "Well done, Harry!"
    // "Buckbeak's Hippogriff Glide can now be accessed from the Mini-Games menu found on the Title Screen."
    RS_ShowRoomDialog(274),
    RS_RespawnRowAndRunChain(14, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(14, 0, 0, 0, 39, 0, 1, 0, 0, 0),
    RS_End(),
};
