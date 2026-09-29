const u8 g_abRoom10V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetOverworldMonstersDisabled(),
    RS_PlayMusicModuleAndFlagIfChain1(16),
    RS_QueueTileObjectMove(2, 1, 0, 0, 1800, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 1, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};
