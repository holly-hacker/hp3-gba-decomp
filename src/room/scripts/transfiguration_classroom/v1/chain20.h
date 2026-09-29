const u8 g_abRoom03V1Chain20[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(5, 0),
    RS_QueueTileObjectMove(3, 0, 0, 0, 1200, 0),
    RS_DespawnTileObject(7, 2),
    RS_StartTileObjectScript(310, 18, 2, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_Unk02(3, 0, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 7, 0, 1, 0, 0, 0),
    RS_End(),
};
