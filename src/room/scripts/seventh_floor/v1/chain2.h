const u8 g_abRoom24V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(22, 0),
    RS_GotoIfQuestStateCompare(240, 0, 0, 0, 0, 2, 0),
    RS_End(),
};
