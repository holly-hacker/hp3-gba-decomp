const u8 g_abRoom06V1Chain3[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectFacing(0, 255, 6),
    // "We'd better hurry up and find seats."
    RS_ShowRoomDialog(86),
    RS_StartTileObjectScript(570, 184, 0, 4, 1, 0, 0, 6, 255, 255, 255),
    RS_StartTileObjectScript(590, 184, 0, 4, 1, 0, 0, 6, 255, 255, 255),
    RS_DespawnTileObject(4, 1),
    RS_RecruitPartyFollower(7),
    RS_StartTileObjectScript(590, 184, 0, 4, 0, 0, 0, 2, 255, 255, 255),
    RS_DespawnTileObject(4, 0),
    RS_RecruitPartyFollower(6),
    RS_SetBattleDefeatState(1),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
