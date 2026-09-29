const u8 g_abRoom15V1Chain35[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "That's it, Harry!"
    RS_ShowRoomDialog(273),
    RS_PlaySoundById(56),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_UnlockMinigame(1),
    RS_StartMinigame(1, 0, 1, 0, 38),
    RS_End(),
};
