const u8 g_abRoom15V1Chain24[] = {
    RS_ArmChainYield(1),
    // "Everyone gather round! That's it - make sure yeh can see."
    RS_ShowRoomDialog(266),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(10, 1, 0, 0, 24, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(8, 0, 0, 0, 26, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(8, 1, 0, 0, 25, 0, 1, 0, 0, 0),
    RS_End(),
};
