const u8 g_abRoom15V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_RespawnRowAndRunChain(2, 0),
    RS_DespawnRoomRowObjects(9),
    RS_Unk02(3, 1, 2),
    RS_Unk02(3, 2, 2),
    RS_Unk02(3, 0, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};
