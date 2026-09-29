const u8 g_abRoom47V1Chain3[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(4, 0),
    RS_DespawnRoomRowObjects(5),
    RS_SetQuestState(2, 230),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectAnimState(0, 1),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_PlaySoundById(39),
    RS_QueueTileObjectMove(1, 1, 0, 0, 1200, 0),
    RS_SetTileObjectAnimState(0, 2),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_ConsumeRoomItem(75),
#ifdef VERSION_JP
    RS_ShowItemRemovedMessage(75),
#endif
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_UnmuteAllMusicChannels(),
    RS_RespawnRowAndRunChain(2, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
