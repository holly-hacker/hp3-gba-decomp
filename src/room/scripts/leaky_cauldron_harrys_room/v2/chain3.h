const u8 g_abRoom41V2Chain3[] = {
    RS_ArmChainYield(1),
    RS_SetQuestState(0, 5),
    RS_SetQuestState(1, 244),
    RS_CancelObjectAnimSequence(0, 255),
    // "Thank goodness for that! I think I'll turn in for the night."
    RS_ShowRoomDialog(23),
    RS_StartTileObjectScript(94, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_PlayRoomSoundEffect(10),
    RS_SetQuestState(0, 26),
    RS_PlayScreenTransitionOut(),
    RS_PlayCutscene(0, 0, 5),
    RS_End(),
};
