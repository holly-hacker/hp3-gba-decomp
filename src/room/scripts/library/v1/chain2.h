const u8 g_abRoom34V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DespawnRoomRowObjects(7),
    // "Let's ask Madam Pince where we can find the book we need."
    RS_ShowRoomDialog(414),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_End(),
};
