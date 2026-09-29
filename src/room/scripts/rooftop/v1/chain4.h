const u8 g_abRoom25V1Chain4[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_RemovePartyFollower(5),
    RS_DelayedRespawnRowAndRunChainFrames(0, 23, 0),
    RS_ArmChainYield(1),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 25, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(23, 0, 0, 0, 25, 0, 1, 0, 0, 0),
    RS_DespawnRoomRowObjects(23),
    RS_Unk2A(5, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 24, 0),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
