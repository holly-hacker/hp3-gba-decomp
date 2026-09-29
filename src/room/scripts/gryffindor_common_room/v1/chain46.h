const u8 g_abRoom29V1Chain46[] = {
    RS_ArmChainYield(1),
    // "Let's go then!"
    // "You aren't going to ride the Firebolt to Hagrid's hut, are you?"
    // "If it makes you feel better, I'll carry it."
    RS_ShowRoomDialog(435),
    RS_Unk02(15, 2, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(15, 2, 0, 0, 47, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(17, 0, 0, 0, 49, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 46, 0, 1, 0, 0, 0),
    RS_End(),
};
