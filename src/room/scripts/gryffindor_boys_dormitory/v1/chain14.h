const u8 g_abRoom28V1Chain14[] = {
    RS_ArmChainYield(1),
    // "It's a note from Hagrid: 'Dear Harry, we lost the trial. Buckbeak's execution date to be fixed. Hagrid'."
    RS_ShowRoomDialog(530),
    // "Oh, no! They can't do this! Buckbeak isn't dangerous! I have to find Ron and Hermione."
    RS_ShowRoomDialog(531),
    RS_DespawnRoomRowObjects(5),
    RS_SetStoryStage(21),
    RS_SetQuestState(43, 25),
    RS_SetQuestState(0, 232),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
