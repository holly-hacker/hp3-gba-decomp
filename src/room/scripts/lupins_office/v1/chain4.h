const u8 g_abRoom26V1Chain4[] = {
    RS_ArmChainYield(1),
    RS_GrantPartyExperience(10, 65535),
    // "Excellent! Excellent, Harry! That was definitely a start!"
    // "Thank you very much, Professor."
    // "Professor Lupin? If you knew my dad, you must've known Sirius Black as well."
    // "I thought I did, Harry. You'd better get off to your common room. It's getting late."
    // "Bye, Professor."
    RS_ShowRoomDialog(494),
    RS_DespawnTileObject(2, 1),
    RS_SetQuestState(1, 230),
    RS_SetQuestState(36, 25),
    RS_SetStoryStage(18),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
