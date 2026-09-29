const u8 g_abRoom06V3Chain1[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectAnimState(0, 0),
    RS_PlaySoundById(14),
    RS_DelayedRespawnRowAndRunChainFrames(15, 0, 24),
    RS_End(),
};
