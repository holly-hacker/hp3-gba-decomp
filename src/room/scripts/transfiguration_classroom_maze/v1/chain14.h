const u8 g_abRoom04V1Chain14[] = {
    RS_GrantPartyExperience(10, 65535),
    RS_CancelObjectAnimSequence(0, 255),
    RS_PlayTileObjectAnimation(3, 0, 10),
    RS_DespawnRoomRowObjects(3),
    RS_DelayedRespawnRowAndRunChainFrames(0, 4, 0),
    RS_DelayedRespawnRowAndRunChainFrames(0, 8, 0),
    RS_StartObjectAnimSequence(4, 0, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_SetTileObjectFacing(0, 255, 6),
    RS_SetTileObjectAnimStateValue(10, 0, 5),
    RS_SetTileObjectAnimStateValue(10, 1, 5),
    RS_SetTileObjectAnimStateValue(10, 2, 5),
    RS_End(),
};
