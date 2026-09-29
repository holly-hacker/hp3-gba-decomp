const u8 g_abRoom38V1Chain5[] = {
    RS_GotoIfQuestStateCompare(243, 0, 1, 0, 0, 0, 0),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(335, 211, 0, 0, 255, 0, 0, 2, 255, 255, 255),
    // "There's the Rat Tonic!"
    RS_ShowRoomDialog(35),
    RS_ArmChainYield(0),
    RS_PlayTileObjectAnimation(3, 0, 0),
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(2, 0, 0),
    RS_PlaySoundById(41),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_ArmChainYield(0),
    RS_PlayTileObjectAnimation(3, 0, 1),
    RS_ArmChainYield(1),
    // "Oh! It's had too much Rat Tonic! I'd better get the rest of the Tonic and get out!"
    RS_ShowRoomDialog(37),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_ArmChainYield(0),
    RS_End(),
};
