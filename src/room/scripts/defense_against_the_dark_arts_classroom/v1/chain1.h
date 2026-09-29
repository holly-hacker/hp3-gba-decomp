const u8 g_abRoom00V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DespawnTileObject(6, 0),
    // "Sorry we're late - oh, Professor Snape!"
    RS_ShowRoomDialog(409),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 5, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(2, 0, 0, 0, 2200, 0),
    RS_End(),
};
