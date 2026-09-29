const u8 g_abRoom25V1Chain6[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 225),
    RS_DespawnTileObject(1, 6),
    RS_DespawnTileObject(1, 0),
    RS_ArmChainYield(1),
    // "A pipe must have burst here. Maybe we should split up?"
    RS_ShowRoomDialog(605),
    // "I bet I can get through very quickly this way. Why don't you peek around the other side and see if there's anything you missed?"
    // "Okay. I'll meet up with you at the tower."
    RS_ShowRoomDialog(607),
    RS_ShowLoadingScreenTransition(27, 28, 32, 255),
    RS_GotoIfStoryStageCompare(0, 27, 5, 0, 0, 0),
    RS_GotoIfStoryStageCompare(0, 28, 6, 0, 0, 0),
    RS_End(),
};
