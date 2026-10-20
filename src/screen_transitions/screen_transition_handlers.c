#include "types.h"
#include "screen_transitions.h"

const ScreenTransitionHandler g_apfnScreenTransitionsIn[15] = {
    sub_0803D4A8,
    sub_0803D508,
    PlayPaletteFadeTransition_candidate,
    sub_0803C690,
    sub_0803D568,
    sub_0803C714,
    sub_0803D5E8,
    sub_0803C798,
    sub_0803C8DC,
    sub_0803CA18,
    sub_0803CB5C,
    sub_0803CC98,
    sub_0803CE54,
    sub_0803CFF4,
    sub_0803D668,
};

const ScreenTransitionHandler g_apfnScreenTransitionsOut[15] = {
    sub_0803D70C,
    sub_0803D76C,
    sub_0803C538,
    sub_0803D7CC,
    sub_0803D848,
    sub_0803D8D0,
    sub_0803D94C,
    sub_0803C848,
    sub_0803C96C,
    sub_0803CAC8,
    sub_0803CBEC,
    sub_0803CD7C,
    sub_0803CF24,
    sub_0803D164,
    sub_0803D9D8,
};
