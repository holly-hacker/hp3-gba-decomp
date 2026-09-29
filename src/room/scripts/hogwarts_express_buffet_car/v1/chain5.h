const u8 g_abRoom07V1Chain5[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "Better return to your seat, miss. We'll be at Hogsmeade very shortly."
    RS_ShowRoomDialog(133),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
