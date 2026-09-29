const u8 g_abRoom11V1Chain16[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(9, 0, 0, 0, 1000, 0),
    // "Squeak!"
    // "It's Scabbers! Scabbers, what are you doing here?"
    RS_ShowRoomDialog(547),
    RS_DespawnRoomRowObjects(10),
    // "They're comin' - Macnair, the executioner, and Fudge. Yeh'd best leave now."
    // "We'll be back, Hagrid..."
    RS_ShowRoomDialog(548),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_StartObjectAnimSequence(9, 0, 0, 0, 18, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(9, 1, 0, 0, 19, 0, 1, 0, 0, 0),
    RS_End(),
};
