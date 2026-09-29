const u8 g_abRoom41V2Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(94, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_PlayTileObjectAnimation(2, 0, 11),
    RS_SetStoryStage(31),
    RS_DespawnTileObject(2, 0),
    RS_StartBattle(0, 0, 4),
    RS_End(),
};
