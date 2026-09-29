const u8 g_abRoom06V1Chain4[] = {
    RS_SetTileObjectAnimState(0, 0),
    RS_CancelObjectAnimSequence(0, 255),
    RS_PlaySoundById(14),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 28),
    RS_End(),
};
