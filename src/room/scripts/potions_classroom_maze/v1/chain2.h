const u8 g_abRoom02V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_GrantPartyExperience(10, 65535),
    RS_PlayRoomSoundEffect(24),
    RS_DelayedRespawnRowAndRunChain(0, 2, 0),
    RS_SetQuestState(21, 25),
    // "There, we have all the ingredients. Now we need to get them back to class."
    RS_ShowRoomDialog(318),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
