const u8 g_abRoom24V1Chain18[] = {
    RS_ArmChainYield(1),
    RS_PlaySoundById(52),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    RS_GrantPartyExperience(10, 65535),
    RS_PlayRoomSoundEffect(24),
    // "Scabbers! There you are!"
    // "Let's get back to the common room."
    RS_ShowRoomDialog(357),
    RS_DespawnRoomRowObjects(6),
    RS_DespawnRoomRowObjects(5),
    RS_DespawnTileObject(1, 1),
    RS_SetQuestState(2, 245),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_InvokeChainIfEnabled(0, 3),
    RS_End(),
};
