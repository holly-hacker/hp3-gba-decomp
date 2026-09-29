const u8 g_abRoom26V1Chain3[] = {
    RS_ArmChainYield(1),
    // "Glad you came, Harry. Are you ready for the lesson?"
    // "Yes, Professor."
    // "So... The spell I am going to try and teach you is highly advanced magic, Harry. It is called the Patronus Charm."
    // "How does it work?"
    // "It conjures up a Patronus, which is a kind of Anti-Dementor - a guardian which acts as a shield between you and the Dementor."
    // "What does a Patronus look like?"
    // "Each one is unique to the wizard who conjures it."
    // "And how do you conjure it?"
    // "With the incantation - expecto patronum! There is a Boggart in this chest. When you're ready, Harry - begin!"
    // "Expecto patronum!"
    RS_ShowRoomDialog(484),
    RS_UnlockMinigame(4),
    RS_StartMinigame(4, 1, 1, 0, 5),
    RS_End(),
};
