const u8 g_abRoom41V1Chain1[] = {
    RS_SetTileObjectAnimState(0, 0),
    RS_PlayScreenTransitionIn(),
    // "Here, Harry. Take these collector's cards. They might help you during a magical encounter."
    // "Thank you, Minister."
    RS_ShowRoomDialog(5),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
