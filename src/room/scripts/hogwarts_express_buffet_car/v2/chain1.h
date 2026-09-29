const u8 g_abRoom07V2Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "I've sold out of chocolate, I'm afraid."
    RS_ShowRoomDialog(137),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
