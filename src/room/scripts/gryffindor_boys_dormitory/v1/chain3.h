const u8 g_abRoom28V1Chain3[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "Ron? What's going on?"
    // "Black! Sirius Black! With a knife!"
    // "What?"
    // "Here! Just now! Slashed the curtains! Woke me up!!"
    // "We'd better get Professor McGonagall!"
    RS_ShowRoomDialog(506),
    RS_Unk02(6, 0, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(6, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};
