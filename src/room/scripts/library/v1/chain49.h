const u8 g_abRoom34V1Chain49[] = {
    RS_DespawnTileObject(13, 0),
    RS_GrantPartyExperience(50, 65535),
    RS_ResetPartyLeaderSelection(),
    RS_RemovePartyFollower(7),
    RS_RespawnRowAndRunChain(14, 0),
    RS_RemovePartyFollower(6),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 10, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(14, 0, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_End(),
};
