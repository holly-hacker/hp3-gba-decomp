const u8 g_abRoom13V1Chain2[] = {
    RS_SetOverworldMonstersDisabled(),
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_RespawnRowAndRunChain(13, 0),
    RS_SetQuestState(48, 25),
    RS_RecruitPartyFollower(6),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 17, 0, 1, 0, 0, 0),
    RS_End(),
};
