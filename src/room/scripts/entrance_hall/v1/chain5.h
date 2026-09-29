const u8 g_abRoom16V1Chain5[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(16, 0),
    RS_RemovePartyFollower(7),
    RS_RemovePartyFollower(6),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(16, 1, 0, 0, 13, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(16, 0, 0, 0, 12, 0, 1, 0, 0, 0),
    RS_End(),
};
