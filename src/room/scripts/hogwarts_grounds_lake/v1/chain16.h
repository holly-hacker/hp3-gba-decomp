const u8 g_abRoom13V1Chain16[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "What did you do?"
    // "I just saved our lives! Listen, I'll fly Buckbeak up to the West Tower's window... You go there on foot. Maybe one of us will get there in time to rescue Sirius."
    // "And whoever gets there first can set Sirius free! Let's go!"
    // "Come on, Buckbeak, we have to get to Sirius!"
    RS_ShowRoomDialog(604),
    RS_RecruitPartyFollower(6),
    RS_SetQuestState(0, 130),
    RS_UnlockMinigame(1),
    RS_StartMinigame(1, 2, 0, 0, 0),
    RS_End(),
};
