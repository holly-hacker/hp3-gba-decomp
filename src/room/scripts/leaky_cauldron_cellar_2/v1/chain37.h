const u8 g_abRoom39V1Chain37[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "These stairs are broken!"
    RS_ShowRoomDialog(78),
    // "I can fix them with the Reparo Spell."
    RS_ShowRoomDialog(79),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
