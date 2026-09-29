const u8 g_abRoom33V1Chain6[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "What are we supposed to do?"
    // "We're going to use the Time-Turner to go back three hours, rescue Buckbeak and then release Sirius from the West Tower."
    RS_ShowRoomDialog(588),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};
