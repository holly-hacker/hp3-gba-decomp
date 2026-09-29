const u8 g_abRoom15V1Chain70[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(21, 0),
    RS_DespawnTileObject(20, 0),
    // "Help!"
    RS_ShowRoomDialog(555),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1800, 0),
    // "The black dog! It's got Ron!"
    RS_ShowRoomDialog(554),
    RS_RespawnRowAndRunChain(29, 0),
    RS_Unk02(0, 255, 3),
    // "It's dragging him towards the Whomping Willow! And where's Crookshanks?"
    RS_ShowRoomDialog(556),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 54, 0, 1, 0, 0, 0),
    RS_End(),
};
