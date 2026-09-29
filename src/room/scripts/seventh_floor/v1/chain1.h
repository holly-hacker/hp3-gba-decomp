const u8 g_abRoom24V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(2, 7),
    RS_DespawnTileObject(2, 8),
    RS_SetQuestState(1, 240),
    RS_SetQuestState(1, 241),
    RS_SetTileObjectFacing(2, 9, 4),
    // "Why isn't everyone going into the common room?"
    // "Oh, my... haven't you heard, Harry?"
    // "Heard what?"
    // "Over here!"
    // "Oh no..."
    // "The Fat Lady's gone and we can't get into the common room..."
    RS_ShowRoomDialog(373),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 9, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(7, 0, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(22, 1, 0, 0, 1200, 0),
    RS_End(),
};
