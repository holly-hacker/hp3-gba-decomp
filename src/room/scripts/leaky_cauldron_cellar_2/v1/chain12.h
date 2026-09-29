const u8 g_abRoom39V1Chain12[] = {
    // "Got him! It's OK, Scabbers, you're safe now."
    RS_ShowRoomDialog(50),
    RS_DespawnTileObject(12, 5),
    RS_DespawnTileObject(12, 3),
    RS_SetTileObjectAnimState(0, 0),
    RS_SetQuestState(1, 252),
    RS_SetQuestState(54, 25),
    RS_DelayedRespawnRowAndRunChainFrames(0, 0, 47),
    RS_End(),
};
