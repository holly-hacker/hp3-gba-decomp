const u8 g_abEffect6Script[] = {
    BS_SetObjectAnim(6, 0),
    BS_SetOamPriority(1),
    BS_WaitFrames(1),
    BS_JitterPosition(1, 45),
    BS_ShowObject(),
    BS_SetVelocity(253, 0),
    BS_StartOrbitMotion(0, 0),
    BS_WaitFrames(80),
    BS_End(),
};
