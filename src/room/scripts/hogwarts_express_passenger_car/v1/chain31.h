const u8 g_abRoom06V1Chain31[] = {
    RS_SetTileObjectFacing(3, 1, 2),
    RS_RecruitPartyFollower(6),
    RS_DespawnTileObject(3, 1),
    RS_RecruitPartyFollower(7),
    RS_DespawnTileObject(3, 0),
    RS_SetQuestState(10, 25),
    RS_SetTileObjectFlagBit(0, 255, 9),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
