const u8 g_abRoom41V1Chain5[] = {
    RS_SetQuestState(1, 244),
    RS_ArmChainYield(1),
    RS_SetStoryStage(2),
    RS_CancelObjectAnimSequence(0, 255),
    // "You have a new item. To equip it, press START and then select Status/Equip. Select a character, move the cursor over the boxes surrounding that character, and press the A Button to change items."
    RS_ShowRoomDialog(612),
    // "Thank goodness for that! I think I'll turn in for the night."
    RS_ShowRoomDialog(23),
    RS_StartTileObjectScript(94, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_PlayRoomSoundEffect(10),
    RS_PlayScreenTransitionOut(),
    RS_SetQuestState(0, 26),
    RS_PlayCutscene(0, 0, 3),
    RS_End(),
};
