const u8 g_abRoom04V1Chain3[] = {
    RS_PlaySoundById(22),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectAnimState(1, 4),
    RS_DelayedRespawnRowAndRunChainFrames(3, 0, 13),
    RS_GotoIfQuestStateCompare(225, 1, 73, 22, 0, 0, 0),
    RS_End(),
};
