const u8 g_abRoom43V1Chain4[] = {
    RS_ArmChainYield(1),
    RS_RespawnRowAndRunChain(4, 0),
    // "Ron - are you OK? Where's the dog?"
    // "Not a dog. Harry, it's a trap... Black is the dog... he's an Animagus..."
    RS_ShowRoomDialog(572),
    RS_SetTileObjectFacing(3, 0, 2),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(4, 0, 0, 0, 600, 0),
    RS_StartObjectAnimSequence(4, 0, 0, 0, 6, 0, 1, 0, 0, 0),
    RS_End(),
};
