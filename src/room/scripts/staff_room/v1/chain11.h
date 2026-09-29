const u8 g_abRoom27V1Chain11[] = {
    RS_ArmChainYield(1),
    // "Now, are you ready?"
    // "Erm... OK, I s'pose..."
    // "Remember to think of something amusing and cast Riddikulus. I'm going to let the Boggart out of the wardrobe now..."
    RS_ShowRoomDialog(350),
    RS_UnlockMinigame(2),
    RS_StartMinigame(2, 0, 1, 0, 3),
    RS_End(),
};
