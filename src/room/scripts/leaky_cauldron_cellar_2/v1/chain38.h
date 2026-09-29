const u8 g_abRoom39V1Chain38[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "These stairs are broken!"
    RS_ShowRoomDialog(78),
    // "I think we should look for another way in."
    RS_ShowRoomDialog(80),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
