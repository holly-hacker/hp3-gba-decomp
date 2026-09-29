const u8 g_abRoom19V1Chain23[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(9),
    // "Did you find out anything?"
    // "Nothing very positive, I'm afraid."
    // "Oh, poor Hagrid - and poor Buckbeak. Let's go back to the common room."
    RS_ShowRoomDialog(445),
    // "We should be on our way to the Christmas feast in the Great Hall."
    // "Absolutely, Harry! I'm starving!"
    // "I'll see you there. I have - something important to do..."
    RS_ShowRoomDialog(459),
    RS_SetQuestState(2, 230),
    RS_SetQuestState(34, 25),
    RS_SetStoryStage(16),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
