const u8 g_abRoom42V2Chain8[] = {
    RS_ArmChainYield(1),
    // "Harry! How are you?"
    // "Fine, thanks, Mrs. Weasley."
    // "Hello, Harry."
    RS_ShowRoomDialog(15),
    RS_SetQuestState(1, 232),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 1, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 5, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_End(),
};
