const u8 g_abRoom25V1Chain5[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_RemovePartyFollower(5),
    RS_DelayedRespawnRowAndRunChain(0, 12, 0),
    RS_DelayedRespawnRowAndRunChain(0, 23, 0),
    RS_ArmChainYield(1),
    RS_StartObjectAnimSequence(23, 0, 0, 0, 26, 0, 1, 0, 0, 0),
    RS_DespawnRoomRowObjects(23),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
