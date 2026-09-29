const u8 g_abRoom42V2Chain19[] = {
    RS_ArmChainYield(1),
    // "Hi, Harry! So, you managed to make it through the summer?"
    // "Just about, Ron. Have you heard from Hermione lately?"
    // "I just saw her in Diagon Alley. She was talking about buying a cat..."
    // "Speaking of pets, how's your rat, Scabbers?"
    // "He's been a bit off-color ever since I brought him back from Egypt."
    // "Why don't you give him a dose of Rat Tonic?"
    // "I don't have any Rat Tonic left."
    // "Maybe the innkeeper, Tom, has some. Tell you what, I'll go and ask him."
    RS_ShowRoomDialog(16),
    RS_InvokeChainIfEnabled(0, 2),
    RS_End(),
};
