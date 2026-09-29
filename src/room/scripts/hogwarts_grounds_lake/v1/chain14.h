const u8 g_abRoom13V1Chain14[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_PlaySoundById(88),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "EXPECTO PATRONUM!"
    RS_ShowRoomDialog(603),
    RS_PlayCutscene(14, 0, 17),
    RS_End(),
};
