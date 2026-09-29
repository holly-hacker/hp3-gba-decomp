const u8 g_abRoom15V1Chain40[] = {
    RS_ArmChainYield(1),
    // "It's Potions next..."
    // "I don't know what you're groaning about, Harry, I'm really looking forward to it!"
    // "What?!"
    // "Just joking - I'm dreading it as much as you."
    // "I've heard we're learning how to make a Shrinking Solution today. Let's go."
    RS_ShowRoomDialog(286),
    RS_Unk02(14, 0, 2),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 45, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(12, 0, 0, 0, 46, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(12, 1, 0, 0, 47, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(14, 0, 0, 0, 48, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(13, 0, 0, 0, 62, 0, 1, 0, 0, 0),
    RS_End(),
};
