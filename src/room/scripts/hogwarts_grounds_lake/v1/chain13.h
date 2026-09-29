const u8 g_abRoom13V1Chain13[] = {
    RS_ArmChainYield(1),
    RS_SetQuestState(53, 25),
    RS_SetQuestState(0, 129),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "The Dementors almost have Sirius! Where are you, Dad? Wait a minute, it wasn't Dad, it was¸ me."
    // "Harry. Hurry up!"
    // "Wait here, Hermione¸"
    RS_ShowRoomDialog(602),
    RS_DespawnRoomRowObjects(8),
    RS_RespawnRowAndRunChain(10, 0),
    RS_RespawnRowAndRunChain(11, 0),
    RS_QueueTileObjectMove(11, 1, 0, 0, 2000, 0),
    RS_RemovePartyFollower(8),
    RS_RemovePartyFollower(6),
    RS_RespawnRowAndRunChain(9, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(10, 0, 0, 0, 13, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(10, 1, 0, 0, 14, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(10, 2, 0, 0, 15, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(10, 3, 0, 0, 16, 0, 1, 0, 0, 0),
    RS_End(),
};
