const u8 g_abRoom29V1Chain48[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetTileObjectFacing(0, 255, 7),
    RS_QueueTileObjectMove(0, 255, 0, 0, 2000, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "I don't believe it - it's a Firebolt racing broom! There's no card, though. I wonder who sent it?"
    // "Wait 'til Malfoy sees you on this! He'll be sick as a pig!"
    // "I can't believe this. Who - ?"
    // "I know who it could've been - Lupin!"
    // "I can't see Lupin affording something like this."
    RS_ShowRoomDialog(433),
    RS_QueueTileObjectMove(15, 2, 0, 0, 2000, 0),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DespawnRoomRowObjects(16),
    // "It's a bit odd, isn't it? Maybe we should get Professor McGonagall to check it out?"
    // "I'm sure it's all right, Hermione. I can't wait to show Hagrid. Let's go find him!"
    RS_ShowRoomDialog(434),
    RS_InvokeChainIfEnabled(0, 47),
    RS_End(),
};
