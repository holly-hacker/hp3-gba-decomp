const u8 g_abRoom40V1Chain4[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    // "C'mon you lot! We need to leave for King's Cross station right away if we want to catch the Hogwarts Express!"
    RS_ShowRoomDialog(77),
    RS_ClearQuestStateUpperHalf(),
    RS_SetStoryStage(7),
    RS_ResetPartyLeaderSelection(),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(9, 25),
    RS_SetOverworldMonstersDisabled(),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlayCutscene(0, 0, 7),
    RS_End(),
};
