const u8 g_abRoom45V1Chain27[] = {
    RS_RemovePartyFollower(5),
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1500, 0),
    RS_DelayedRespawnRowAndRunChainFrames(0, 2, 0),
    RS_DespawnTileObject(1, 4),
    RS_DelayedRespawnRowAndRunChainFrames(0, 22, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
