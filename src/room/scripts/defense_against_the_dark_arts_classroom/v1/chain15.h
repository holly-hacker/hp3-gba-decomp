const u8 g_abRoom00V1Chain15[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetTileObjectFacing(2, 0, 2),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "This is... acceptable."
    RS_ShowRoomDialog(425),
    RS_SetTileObjectFacing(0, 255, 6),
    RS_GrantPartyExperience(10, 65535),
    RS_PlayRoomSoundEffect(24),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_RemovePartyFollower(6),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1800, 0),
    RS_SetTileObjectFacing(0, 255, 6),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(9, 0, 0, 0, 12, 0, 1, 0, 0, 0),
    RS_End(),
};
