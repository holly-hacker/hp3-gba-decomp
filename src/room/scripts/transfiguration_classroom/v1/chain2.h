const u8 g_abRoom03V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(4, 0),
    RS_RemovePartyFollower(7),
    RS_SetTileObjectFacing(4, 0, 0),
    RS_SetTileObjectFacing(0, 255, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_QueueTileObjectMove(2, 0, 0, 0, 1400, 0),
    // "Attention, class! Today's lesson will concern Animagi."
    // "Animagi are wizards who can transform at will into animals. Like this..."
    RS_ShowRoomDialog(198),
    RS_DespawnRoomRowObjects(3),
    RS_DespawnRoomRowObjects(4),
    RS_RespawnRowAndRunChain(7, 0),
    RS_PlayTileObjectAnimation(2, 0, 9),
    RS_StartTileObjectScript(310, 93, 2, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_PauseMusic(),
    RS_PlaySoundById(62),
    RS_QueueTileObjectMove(6, 7, 0, 0, 1200, 0),
    RS_QueueTileObjectMove(6, 6, 0, 0, 600, 0),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    RS_QueueTileObjectMove(6, 7, 0, 0, 600, 0),
    RS_QueueTileObjectMove(2, 0, 0, 0, 1200, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlayTileObjectAnimation(2, 0, 10),
    RS_UnmuteAllMusicChannels(),
    RS_ResumeMusic(),
    // "What's got into you all today? That's the first time my transformation's not got applause from a class."
    // "Now - I need someone to assist me in a Transfiguration challenge. Any volunteers?"
    RS_ShowRoomDialog(199),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_InvokeChainIfEnabled(0, 16),
    RS_End(),
};
