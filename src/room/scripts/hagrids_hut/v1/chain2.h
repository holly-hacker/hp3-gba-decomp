const u8 g_abRoom11V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ResetPartyLeaderSelection(),
    RS_RespawnRowAndRunChain(6, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_End(),
};
