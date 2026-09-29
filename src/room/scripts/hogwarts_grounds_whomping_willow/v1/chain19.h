const u8 g_abRoom15V1Chain19[] = {
    RS_ArmChainYield(1),
    // "Righ', then, so... so yeh've got yer books an'... an'... if you'd like to follow me to the paddock we can start the lesson."
    RS_ShowRoomDialog(264),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 14, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(15, 0, 0, 0, 18, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_StartObjectAnimSequence(15, 2, 0, 0, 20, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(15, 1, 0, 0, 22, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(15, 3, 0, 0, 21, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(15, 4, 0, 0, 21, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(15, 5, 0, 0, 21, 0, 1, 0, 0, 0),
    RS_End(),
};
