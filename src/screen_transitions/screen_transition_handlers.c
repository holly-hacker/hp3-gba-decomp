#include "types.h"
#include "screen_transitions.h"

const ScreenTransitionHandler g_apfnScreenTransitionsIn[15] = {
    TransitionInFadeFromBlack,
    TransitionInFadeFromWhite,
    TransitionInPaletteFade,
    TransitionInWipeDown,
    TransitionInWipeUp,
    TransitionInWipeRight,
    TransitionInWipeLeft,
    TransitionInSplitHorizontal,
    TransitionInConvergeHorizontal,
    TransitionInSplitVertical,
    TransitionInConvergeVertical,
    TransitionInBoxExpand,
    TransitionInBoxShrink,
    TransitionInMosaic,
    TransitionInLetterbox,
};

const ScreenTransitionHandler g_apfnScreenTransitionsOut[15] = {
    TransitionOutFadeToBlack,
    TransitionOutFadeToWhite,
    TransitionOutPaletteFade,
    TransitionOutWipeDown,
    TransitionOutWipeUp,
    TransitionOutWipeRight,
    TransitionOutWipeLeft,
    TransitionOutSplitHorizontal,
    TransitionOutConvergeHorizontal,
    TransitionOutSplitVertical,
    TransitionOutConvergeVertical,
    TransitionOutBoxExpand,
    TransitionOutBoxShrink,
    TransitionOutMosaic,
    TransitionOutLetterbox,
};
