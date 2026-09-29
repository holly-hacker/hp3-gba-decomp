const u8 g_abRoom42V2Chain5[] = {
    // "Excuse me, Tom, I don't suppose you have any Rat Tonic?"
    // "Indeed I do, Mr. Potter. If you don't mind finding your own way, there's a bottle down in the cellar. It's dark down there, so you might need to use Lumos to find your way."
    // "I'm sure I can find the Rat Tonic for Ron..."
    RS_ShowRoomDialog(29),
    RS_DelayedRespawnRowAndRunChain(0, 4, 19),
    RS_SetStoryStage(4),
    RS_End(),
};
