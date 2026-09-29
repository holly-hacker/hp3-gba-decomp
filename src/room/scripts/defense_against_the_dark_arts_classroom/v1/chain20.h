const u8 g_abRoom00V1Chain20[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(11),
    RS_SetTileObjectFacing(9, 0, 6),
    RS_RecruitPartyFollower(7),
    RS_RecruitPartyFollower(6),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 18, 0, 1, 0, 0, 0),
    RS_End(),
};
