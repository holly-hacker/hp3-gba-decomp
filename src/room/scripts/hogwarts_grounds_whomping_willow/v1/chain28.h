const u8 g_abRoom15V1Chain28[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(8, 2, 0, 0, 1600, 0),
    RS_RespawnRowAndRunChain(24, 0),
    RS_DespawnTileObject(10, 1),
    // "I'm dying! Look at me! It's killed me!"
    // "Yer not dyin'! Someone help me - gotta get him outta here, gotta get him to Madam Pomfrey..."
    RS_ShowRoomDialog(270),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(8, 2, 0, 0, 31, 0, 1, 0, 0, 0),
    RS_End(),
};
