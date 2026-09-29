const u8 g_abRoom00V1Chain8[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(2, 0, 4),
    RS_RespawnRowAndRunChain(4, 0),
    RS_RespawnRowAndRunChain(3, 0),
    RS_RemovePartyFollower(6),
    RS_RemovePartyFollower(7),
    // "This lesson began ten minutes ago, Potter. Sit down."
    RS_ShowRoomDialog(410),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 19, 0, 1, 0, 0, 0),
    RS_End(),
};
