const u8 g_abRoom45V1Chain40[] = {
    RS_DespawnRoomRowObjects(15),
    RS_SetTileObjectAnimState(16, 1),
    RS_DelayedRespawnRowAndRunChainFrames(0, 10, 0),
    RS_GotoIfQuestStateCompare(227, 0, 0, 54, 0, 0, 0),
    RS_SetQuestState(1, 227),
    RS_End(),
};
