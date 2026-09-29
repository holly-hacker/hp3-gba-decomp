const u8 g_abRoom29V1Chain45[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_QueueTileObjectMove(15, 2, 0, 0, 1400, 0),
    // "Something wrong?"
    RS_ShowRoomDialog(430),
    RS_DespawnTileObject(15, 1),
    RS_DespawnTileObject(15, 0),
    RS_RespawnRowAndRunChain(17, 0),
    RS_RespawnRowAndRunChain(16, 0),
    RS_RemovePartyFollower(7),
    // "Hedwig dropped a parcel on top of that notice board and we don't know how to get to it."
    // "Why don't you just use Wingardium Leviosa?"
    RS_ShowRoomDialog(431),
    // "Wingardium Leviosa!"
    RS_ShowRoomDialog(432),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 48, 0, 1, 0, 0, 0),
    RS_End(),
};
