const u8 g_abRoom39V1Chain39[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "This door's locked!"
    RS_ShowRoomDialog(81),
    // "I think we should look for another way in."
    RS_ShowRoomDialog(82),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
