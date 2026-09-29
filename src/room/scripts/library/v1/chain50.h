const u8 g_abRoom34V1Chain50[] = {
    // "Excellent, you have all the pages! Would you like to repair the book now, please?"
    RS_ShowRoomDialog(417),
    RS_CancelObjectAnimSequence(0, 255),
    RS_PlayTileObjectAnimation(14, 0, 8),
    RS_ArmChainYield(1),
    RS_ArmChainYield(0),
    RS_PlaySoundById(73),
    RS_End(),
};
