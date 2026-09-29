const u8 g_abRoom15V1Chain66[] = {
    RS_ArmChainYield(1),
    // "How could they execute Buckbeak - how could they?"
    // "Scabbers, keep still!"
    // "Squeak!"
    // "Ouch! Scabbers bit me!"
    RS_ShowRoomDialog(551),
    RS_RespawnRowAndRunChain(19, 0),
    RS_Unk02(19, 0, 5),
    RS_Unk02(19, 1, 5),
    // "Yeowwl!"
    RS_ShowRoomDialog(552),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(19, 0, 0, 0, 65, 0, 1, 0, 0, 0),
    RS_End(),
};
