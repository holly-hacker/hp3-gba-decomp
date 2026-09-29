const u8 g_abRoom15V1Chain47[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 26),
    RS_SetOverworldMonstersDisabled(),
    RS_RemovePartyFollower(6),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "You're free, Sirius."
    // "Yes, thank you all. Harry, your parents named me your godfather. Once my name's cleared... if you wanted a... a different home¸"
    // "When can I move in?"
    RS_ShowRoomDialog(577),
    RS_RespawnRowAndRunChain(18, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(18, 0, 0, 0, 50, 0, 1, 0, 0, 0),
    RS_End(),
};
