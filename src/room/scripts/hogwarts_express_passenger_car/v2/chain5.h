const u8 g_abRoom06V2Chain5[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(189, 153, 0, 0, 255, 0, 0, 1, 255, 255, 255),
    // "There you are, Harry!"
    // "Um... Hello..."
    // "I am Cornelius Fudge, Harry, the Minister for Magic."
    // "Hello, Mr. Fudge. Have you had any luck with catching Sirius Black yet?"
    // "What's that?"
    // "Sirius Black, the murderer who killed thirteen people with a single curse and who recently escaped from Azkaban prison?"
    // "Oh, that Sirius Black - well, no, not yet, but it's only a matter of time. The Azkaban guards have never yet failed. Now, allow me to escort you to your room. Follow me closely - we don't want you getting lost¸"
    // "All right, thank you."
    RS_ShowRoomDialog(0),
    RS_StartTileObjectScript(173, 216, 0, 0, 255, 0, 0, 4, 255, 255, 255),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
