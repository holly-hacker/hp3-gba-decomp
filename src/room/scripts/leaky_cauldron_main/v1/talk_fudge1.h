// First conversation with Fudge
const u8 g_abRoom42TalkFudge1[] = {
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(419, 10, 2, 0, 255, 0, 0, 0, 255, 255, 255),
    // "There you are, Harry!"
    // "Um... Hello..."
    // "I am Cornelius Fudge, Harry, the Minister for Magic."
    // "Hello, Mr. Fudge. Have you had any luck with catching Sirius Black yet?"
    // "What's that?"
    // "Sirius Black, the murderer who killed thirteen people with a single curse and who recently escaped from Azkaban prison?"
    // "Oh, that Sirius Black - well, no, not yet, but it's only a matter of time. The Azkaban guards have never yet failed. Now, allow me to escort you to your room. Follow me closely - we don't want you getting lost¸"
    // "All right, thank you."
    RS_ShowRoomDialog(0),
    RS_ArmChainYield(0),
    RS_Unk02(3, 1, 2),
    RS_StartObjectAnimSequence(3, 1, 0, 4, 0, 0, 1, 0, 0, 0),
    RS_ArmChainYield(1),
    RS_SetQuestState(1, 224),
    RS_SetQuestState(1, 0),
    RS_End(),
};
