const u8 g_abRoom15V1Chain69[] = {
    RS_ArmChainYield(1),
    RS_Unk02(20, 0, 4),
    RS_Unk02(21, 0, 4),
    RS_SetTileObjectSpecialFlag(20, 0, 1),
    RS_PlaySoundById(48),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 0),
    RS_ArmChainYield(0),
    RS_PlayTileObjectAnimation(20, 0, 22),
    RS_StartObjectAnimSequence(21, 0, 0, 0, 53, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(20, 0, 0, 0, 53, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(20, 0, 0, 0, 800, 0),
    RS_End(),
};
