const u8 g_abRoom29V1Chain23[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(19, 0),
    // "Well, here it is. There doesn't seem to be anything wrong with the Firebolt at all."
    // "I can have it back? Seriously?"
    // "Seriously. And Potter - do try and win, won't you?"
    RS_ShowRoomDialog(495),
    RS_DespawnRoomRowObjects(19),
    RS_GrantRoomReward(67, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(10, 2, 0, 0, 20, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 19, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(10, 1, 0, 0, 16, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(10, 1, 0, 0, 800, 0),
    RS_End(),
};
