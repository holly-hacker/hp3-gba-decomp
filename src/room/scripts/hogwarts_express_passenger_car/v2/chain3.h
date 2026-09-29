const u8 g_abRoom06V2Chain3[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255),
    // "Here's the chocolate, Professor!"
    // "Well done, Mr. Weasley."
    RS_ShowRoomDialog(138),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
