const u8 g_abRoom24V1Chain23[] = {
    RS_ArmChainYield(1),
    // "Have at thee, scurvy knave!"
    // "The Fat Lady must be in another portrait..."
    // "Why don't we ask Sir Cadogan? He's bonkers, but he knows all about this floor."
    // "OK, we have to start somewhere."
    // "Hello, Sir Cadogan."
    // "I don't suppose you happened to see the Fat Lady go by here?"
    // "That I did, fair maiden, and in great distress!"
    // "Could you help us find her?"
    // "That I shall, milady, and verily so!"
    RS_ShowRoomDialog(376),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_DespawnRoomRowObjects(22),
    RS_InvokeChainIfEnabled(0, 4),
    RS_End(),
};
