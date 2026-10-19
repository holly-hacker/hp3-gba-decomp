#include "sound.h"
#include "3rd_party/krawall.h"

// Nonzero while `handle` still refers to a playing sound.
s32 IsSoundActive(s32 handle)
{
    return kramHandleValid(handle);
}
