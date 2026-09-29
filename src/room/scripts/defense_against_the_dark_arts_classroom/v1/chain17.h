const u8 g_abRoom00V1Chain17[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(9),
    // "Ever get the feeling there's something funny going on with her?"
    // "More and more... C'mon, let's get back to the common room."
    RS_ShowRoomDialog(427),
    RS_ClearQuestStateUpperHalf(),
    RS_SetQuestState(30, 25),
    RS_SetStoryStage(14),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
