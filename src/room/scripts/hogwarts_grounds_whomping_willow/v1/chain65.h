const u8 g_abRoom15V1Chain65[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    RS_PlaySoundById(46),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlayMusicModuleAndFlagIfChain1(16),
    // "What was that? It sounded like..."
    // "Oh, no!"
    // "They did it! I d-don't believe it - they executed Buckbeak!"
    RS_ShowRoomDialog(549),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 52, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(20, 0, 0, 0, 64, 0, 1, 0, 0, 0),
    RS_End(),
};
