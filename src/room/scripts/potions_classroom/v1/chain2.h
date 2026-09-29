const u8 g_abRoom01V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(3, 0, 0, 0, 1850, 0),
    RS_Unk02(3, 1, 5),
    RS_SetTileObjectFacing(3, 1, 2),
    RS_SetTileObjectFacing(3, 1, 4),
    RS_SetTileObjectFacing(3, 1, 6),
    RS_StartTileObjectScript(218, 210, 0, 3, 1, 0, 0, 6, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DespawnTileObject(3, 1),
    // "Settle down, settle down. Today we shall be making a new potion, a Shrinking Solution."
    RS_ShowRoomDialog(295),
    RS_Unk02(3, 0, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_End(),
};
