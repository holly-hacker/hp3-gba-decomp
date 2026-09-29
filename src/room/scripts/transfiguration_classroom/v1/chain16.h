const u8 g_abRoom03V1Chain16[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_RecruitPartyFollower(6),
    RS_DespawnTileObject(3, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 6, 0, 1, 0, 0, 0),
    RS_End(),
};
