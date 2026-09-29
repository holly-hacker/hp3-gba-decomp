const u8 g_abRoom15V1Chain42[] = {
    RS_ArmChainYield(1),
    RS_ResetPartyLeaderSelection(),
    RS_GotoIfQuestStateCompare(229, 4, 5, 0, 0, 7, 0),
    RS_GotoIfQuestStateCompare(229, 0, 5, 65, 0, 6, 0),
    RS_GotoIfQuestStateCompare(229, 0, 6, 23, 0, 0, 0),
    RS_End(),
};
