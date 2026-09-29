const u8 g_abRoom04V1Chain8[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_Unk02(2, 1, 3),
    RS_Unk02(2, 0, 3),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 1, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_SetQuestState(23, 5),
    RS_GrantPartyExperience(10, 65535),
    RS_DelayedRespawnRowAndRunChainFrames(5, 0, 24),
    RS_End(),
};
