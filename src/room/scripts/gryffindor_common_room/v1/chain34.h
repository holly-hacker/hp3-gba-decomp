const u8 g_abRoom29V1Chain34[] = {
    RS_ArmChainYield(1),
    // "I am delighted that Gryffindor won the match, but this is getting ridiculous!"
    // "Ron had a nightmare, Professor."
    // "IT WASN'T A NIGHTMARE! SIRIUS BLACK WAS STANDING OVER ME, HOLDING A KNIFE!"
    RS_ShowRoomDialog(508),
    RS_Unk02(13, 2, 3),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(13, 2, 0, 0, 35, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(13, 0, 0, 0, 1000, 0),
    RS_End(),
};
