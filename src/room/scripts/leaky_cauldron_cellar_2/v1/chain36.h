const u8 g_abRoom39V1Chain36[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "This door's locked!"
    RS_ShowRoomDialog(81),
    // "I can use the Alohomora Spell to unlock it."
    RS_ShowRoomDialog(83),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
