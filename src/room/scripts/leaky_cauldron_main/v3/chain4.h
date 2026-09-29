const u8 g_abRoom42V3Chain4[] = {
    RS_ArmChainYield(0),
    RS_StartTileObjectScript(527, 186, 1, 3, 1, 0, 0, 0, 255, 255, 255),
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(547, 192, 1, 3, 0, 0, 0, 0, 255, 255, 255),
    RS_SetTileObjectFacing(3, 1, 0),
    // "Hermione - we were wondering when you'd show up!"
    // "It's really good to see you both again. I'd like you to meet my new cat, Crookshanks."
    // "You bought that monster?"
    // "He's gorgeous, isn't he?"
    // "Squeak! Squeeeeeak!"
    // "That beast of yours is scaring Scabbers! Keep it away from him!"
    // "Meoww!"
    RS_ShowRoomDialog(45),
    RS_DelayedRespawnRowAndRunChainFrames(3, 0, 6),
    RS_End(),
};
