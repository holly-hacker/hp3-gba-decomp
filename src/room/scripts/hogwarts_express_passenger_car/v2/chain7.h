const u8 g_abRoom06V2Chain7[] = {
    RS_DelayedRespawnRowAndRunChain(0, 4, 0),
    RS_SetAllQueuedMoveParams(0, 1, 0, 0, 65535),
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(190, 148, 0, 0, 255, 0, 0, 6, 255, 255, 255),
    // "Job done, Professor Lupin."
    // "Thank you, Miss Granger."
    RS_ShowRoomDialog(139),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
