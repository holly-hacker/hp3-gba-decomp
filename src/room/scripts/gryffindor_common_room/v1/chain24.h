const u8 g_abRoom29V1Chain24[] = {
    RS_ArmChainYield(1),
    RS_DespawnTileObject(10, 2),
    // "Seen Ron around?"
    // "No, I haven't."
    RS_ShowRoomDialog(496),
    RS_Unk02(10, 3, 2),
    RS_SetTileObjectFacing(10, 1, 0),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(10, 3, 0, 0, 800, 0),
    RS_StartObjectAnimSequence(10, 3, 0, 0, 21, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 23, 0, 1, 0, 0, 0),
    RS_End(),
};
