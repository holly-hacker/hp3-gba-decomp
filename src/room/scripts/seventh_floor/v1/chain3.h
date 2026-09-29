const u8 g_abRoom24V1Chain3[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(8),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1200, 0),
    RS_SetTileObjectFacing(0, 255, 7),
    RS_SetTileObjectFacing(7, 0, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "We need to find her! Come on, Ron. Harry, why don't you stay here in case she comes back?"
    RS_ShowRoomDialog(374),
    // "OK."
    RS_ShowRoomDialog(375),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 9, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(7, 0, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_End(),
};
