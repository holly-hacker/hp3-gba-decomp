const u8 g_abRoom25V1Chain3[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 225),
    RS_DespawnTileObject(1, 0),
    RS_DespawnTileObject(0, 0),
    RS_ArmChainYield(1),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 24, 0, 1, 0, 0, 0),
    RS_ArmChainYield(0),
    RS_DelayedRespawnRowAndRunChainFrames(0, 21, 0),
    RS_RemovePartyFollower(6),
    RS_ArmChainYield(1),
    RS_PlaySoundById(177),
    // "Hermione, I'll go this way. Maybe you could try looking around for a faster route?"
    // "Okay. I'll meet up with you at the tower."
    RS_ShowRoomDialog(606),
    RS_ShowLoadingScreenTransition(27, 28, 32, 255),
    RS_GotoIfStoryStageCompare(0, 27, 44, 0, 0, 0),
    RS_GotoIfStoryStageCompare(0, 28, 45, 0, 0, 0),
    RS_End(),
};
