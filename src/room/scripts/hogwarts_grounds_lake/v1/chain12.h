const u8 g_abRoom13V1Chain12[] = {
    RS_ArmChainYield(1),
    // "I know what to do! Arrrrrooooooooh!"
    RS_ShowRoomDialog(599),
    RS_PlaySoundById(54),
    RS_StartTileObjectScript(72, 77, 1, 8, 0, 0, 0, 0, 255, 255, 255),
    // "Well done, Hermione!"
    RS_ShowRoomDialog(596),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_Unk02(8, 0, 2),
    // "Here comes Lupin! Help, Buckbeak!"
    RS_ShowRoomDialog(597),
    RS_ArmChainYield(0),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1000, 0),
    RS_StartObjectAnimSequence(8, 0, 0, 0, 11, 0, 1, 0, 0, 0),
    RS_End(),
};
