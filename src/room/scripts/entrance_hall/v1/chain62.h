const u8 g_abRoom16V1Chain62[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(16),
    RS_RecruitPartyFollower(6),
    RS_RecruitPartyFollower(7),
    RS_SetQuestState(2, 224),
    RS_RespawnRowAndRunChain(3, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 16, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 2, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 1, 0, 0, 5, 0, 1, 0, 0, 0),
    RS_End(),
};
