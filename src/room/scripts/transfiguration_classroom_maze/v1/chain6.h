const u8 g_abRoom04V1Chain6[] = {
    RS_PlaySoundById(22),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetTileObjectAnimState(9, 4),
    RS_DelayedRespawnRowAndRunChainFrames(3, 0, 13),
    RS_GotoIfQuestStateCompare(229, 1, 19, 23, 0, 0, 0),
    RS_End(),
};
