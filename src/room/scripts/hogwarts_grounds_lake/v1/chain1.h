const u8 g_abRoom13V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_PlayMusicModuleAndFlagIfChain1(9),
    RS_RespawnRowAndRunChain(3, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_DespawnRoomRowObjects(2),
    RS_End(),
};
