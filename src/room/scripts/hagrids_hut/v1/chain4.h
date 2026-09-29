const u8 g_abRoom11V1Chain4[] = {
    RS_ArmChainYield(1),
    // "Yeh've heard!"
    // "Hagrid, what is it?"
    RS_ShowRoomDialog(437),
    RS_DespawnRoomRowObjects(12),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(6, 0, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 5, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(5, 0, 0, 0, 6, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(4, 0, 0, 0, 7, 0, 1, 0, 0, 0),
    RS_End(),
};
