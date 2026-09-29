const u8 g_abRoom25V1Chain44[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    RS_StartObjectAnimSequence(21, 0, 0, 0, 24, 0, 1, 0, 0, 0),
    RS_DespawnRoomRowObjects(21),
    RS_Unk2A(6, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 22, 0),
    RS_DelayedRespawnRowAndRunChain(0, 12, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
