const u8 g_abRoom03V1Chain1[] = {
    RS_ArmChainYield(0),
    RS_ResetPartyLeaderSelection(),
    RS_SetQuestState(1, 2),
    RS_RespawnRowAndRunChain(2, 0),
    RS_RespawnRowAndRunChain(6, 0),
    RS_End(),
};
