const u8 g_abRoom29V1Chain14[] = {
    RS_ArmChainYield(1),
    RS_PlaySoundById(52),
    // "Crookshanks! What is wrong with you?"
    // "Just keep that cat away from Scabbers!"
    RS_ShowRoomDialog(355),
    RS_Unk02(5, 0, 4),
    RS_Unk02(5, 1, 4),
    RS_QueueTileObjectMove(5, 0, 0, 0, 1700, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(5, 0, 0, 0, 11, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(5, 1, 0, 0, 12, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 13, 0, 1, 0, 0, 0),
    RS_End(),
};
