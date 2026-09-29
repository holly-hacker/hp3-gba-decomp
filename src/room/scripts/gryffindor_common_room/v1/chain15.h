const u8 g_abRoom29V1Chain15[] = {
    RS_ArmChainYield(1),
    RS_RemovePartyFollower(6),
    RS_RespawnRowAndRunChain(8, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1700, 0),
    RS_DespawnRoomRowObjects(5),
    // "Scabbers, come back!"
    // "I'll help you get him, Ron."
    RS_ShowRoomDialog(356),
    RS_SetQuestState(24, 25),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
