const u8 g_abRoom05V1Chain17[] = {
    RS_SetPauseMenuLocked(1, 255, 255, 255),
    RS_PlayMusicModuleAndFlagIfChain1(9),
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DelayedRespawnRowAndRunChain(0, 18, 0),
    RS_SetQuestState(0, 249),
    RS_StartTileObjectScript(196, 23, 1, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 29, 0),
    RS_InvokeChainIfEnabled(0, 4),
    RS_End(),
};
