const u8 g_abRoom15V1Chain25[] = {
    RS_ArmChainYield(1),
    // "This place is going to the dogs. That oaf teaching classes, my father'll have a fit when I tell him-"
    // "Shut up, Malfoy."
    // "Careful, Potter, there's a Dementor behind you-"
    RS_ShowRoomDialog(267),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(13, 0, 0, 0, 19, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(13, 0, 0, 0, 700, 0),
    RS_End(),
};
