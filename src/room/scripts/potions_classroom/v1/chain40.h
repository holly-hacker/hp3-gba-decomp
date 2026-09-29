const u8 g_abRoom01V1Chain40[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(2),
    RS_DespawnRoomRowObjects(4),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlaySoundById(23),
    RS_ClearQuestStateUpperHalf(),
    RS_RespawnRowAndRunChain(18, 0),
    RS_SetStoryStage(5),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
