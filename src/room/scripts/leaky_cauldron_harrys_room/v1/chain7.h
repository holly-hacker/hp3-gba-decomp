const u8 g_abRoom41V1Chain7[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(103, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlayTileObjectAnimation(2, 0, 11),
    RS_DespawnTileObject(2, 0),
    RS_StartBattle(0, 0, 6),
    RS_End(),
};
