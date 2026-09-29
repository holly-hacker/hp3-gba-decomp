const u8 g_abRoom11V1Chain3[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(12, 0),
    // "Hagrid! Look at my new Firebolt!"
    RS_ShowRoomDialog(436),
    RS_DespawnRoomRowObjects(7),
    RS_RemovePartyFollower(6),
    RS_RespawnRowAndRunChain(4, 0),
    RS_RemovePartyFollower(7),
    RS_RespawnRowAndRunChain(5, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(6, 0, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(4, 0, 0, 0, 2, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(5, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(6, 0, 0, 0, 1000, 0),
    RS_End(),
};
