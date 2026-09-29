const u8 g_abRoom33V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(170, 3, 1, 0, 255, 0, 0, 6, 255, 255, 255),
    // "What we need is more time."
    // "Miss Granger, three turns should do it. Good luck."
    RS_ShowRoomDialog(587),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_PlayCutscene(10, 0, 7),
    RS_End(),
};
