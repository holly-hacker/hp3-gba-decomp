const u8 g_abRoom15V1Chain34[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "Careful, Harry!"
    // "We're friends now. You know, I bet I could ride him..."
    RS_ShowRoomDialog(272),
    RS_PlaySoundById(57),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 38, 0, 1, 0, 0, 0),
    RS_End(),
};
