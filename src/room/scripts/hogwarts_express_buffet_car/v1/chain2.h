const u8 g_abRoom07V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "Have you seen the conductor?"
    // "He was going towards the front of the train, looking very cross, I might add."
    RS_ShowRoomDialog(129),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
