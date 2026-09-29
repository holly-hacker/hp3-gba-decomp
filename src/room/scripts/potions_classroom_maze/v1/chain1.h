const u8 g_abRoom02V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_AddQuestState(1, 231),
    RS_GotoIfQuestStateCompare(231, 3, 4, 3, 0, 0, 0),
    RS_End(),
};
