const u8 g_abRoom06V1Chain2[] = {
    RS_PlaySoundById(63),
    RS_PlayTileObjectAnimation(1, 0, 7),
    RS_SetQuestState(1, 224),
    RS_SetQuestState(9, 25),
    RS_InvokeChainIfEnabled(0, 4),
    RS_SetQuestState(9, 8),
    RS_End(),
};
