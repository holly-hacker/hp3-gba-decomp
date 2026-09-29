const u8 g_abRoom01V1Chain42[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(3, 0, 4),
    RS_SetTileObjectFacing(2, 8, 6),
    // "I require a volunteer to gather ingredients for this potion."
    RS_ShowRoomDialog(296),
    RS_SetQuestState(20, 25),
    RS_ShowLoadingScreenTransition(5, 6, 32, 255),
    RS_GotoIfStoryStageCompare(0, 5, 10, 9, 0, 0),
    RS_End(),
};
