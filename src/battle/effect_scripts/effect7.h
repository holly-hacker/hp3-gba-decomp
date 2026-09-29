const u8 g_abEffect7Script[] = {
    BS_SetObjectAnim(7, 0),
    BS_SetOamPriority(2),
    BS_WaitFrames(1),
    BS_JitterPosition(1, 45),
    BS_ShowObject(),
    BS_SetVelocity(252, 0),
    BS_StartOrbitMotion(0, 0),
    BS_WaitFrames(80),
    BS_End(),
};
