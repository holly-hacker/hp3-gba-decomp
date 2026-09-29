const u8 g_abRoom15V1Chain52[] = {
    RS_ArmChainYield(1),
    RS_RemovePartyFollower(6),
    RS_DespawnTileObject(23, 1),
    RS_ArmChainYield(0),
#ifndef VERSION_JP
    RS_PlaySoundById(46),
#endif
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_ArmChainYield(1),
    RS_RecruitPartyFollower(6),
    RS_RecruitPartyFollower(8),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 58, 0, 1, 0, 0, 0),
    RS_End(),
};
