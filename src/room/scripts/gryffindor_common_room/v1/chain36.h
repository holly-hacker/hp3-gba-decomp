const u8 g_abRoom29V1Chain36[] = {
    RS_ArmChainYield(1),
    // "I - erm - well, I..."
    // "I see. From tonight, Sir Cadogan is sacked and the Fat Lady will return. Security will be increased. Everyone, please be more careful. Now, back to bed."
    RS_ShowRoomDialog(510),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(13, 7, 0, 0, 40, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 0, 0, 0, 39, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 1, 0, 0, 37, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 3, 0, 0, 66, 1, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 4, 0, 0, 66, 1, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 6, 0, 0, 64, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 5, 0, 0, 38, 1, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 2, 0, 0, 39, 0, 1, 0, 0, 0),
    RS_End(),
};
