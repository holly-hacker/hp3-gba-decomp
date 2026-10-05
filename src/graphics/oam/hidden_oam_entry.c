#include "types.h"
#include "graphics/oam.h"

// OAM entry with the OBJ disabled (attribute 0 affine mode 2), copied into
// every shadow slot by ClearOamShadowBuffers.
const OamEntry g_HiddenOamEntry = {
    0, 2,
};
