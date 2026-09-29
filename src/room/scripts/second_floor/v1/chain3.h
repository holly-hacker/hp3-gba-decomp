const u8 g_abRoom19V1Chain3[] = {
    RS_ArmChainYield(1),
    // "Hello, are you all right?"
    // "Oh, it was horrible... horrible!"
    // "What happened?"
    // "He's got a dreadful temper!"
    // "Who? Who has?"
    // "Sirius Black!"
    // "We have to warn Harry!"
    // "Come on, then - back to the common room!"
    RS_ShowRoomDialog(391),
    RS_SetQuestState(2, 249),
    RS_Unk02(0, 255, 1),
    RS_SetQuestState(23, 25),
    RS_SetQuestState(2, 245),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_GrantPartyExperience(10, 65535),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
