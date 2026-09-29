const u8 g_abRoom15V1Chain51[] = {
    RS_ArmChainYield(1),
    // "Who's that at the door?"
    RS_ShowRoomDialog(592),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "That must be us! We don't have much time before Macnair, the executioner, shows up."
    RS_ShowRoomDialog(593),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(23, 0, 0, 0, 56, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 57, 0, 1, 0, 0, 0),
    RS_End(),
};
