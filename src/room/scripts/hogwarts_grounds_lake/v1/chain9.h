const u8 g_abRoom13V1Chain9[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "Dad?"
    RS_ShowRoomDialog(586),
    RS_SetQuestState(50, 25),
    RS_ReturnToOverworld(33, 2),
    RS_End(),
};
