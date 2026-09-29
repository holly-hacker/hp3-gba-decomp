const u8 g_abRoom06V2Chain6[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255),
    // "Job done, Professor Lupin."
    // "Thank you, Miss Granger."
    RS_ShowRoomDialog(139),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
