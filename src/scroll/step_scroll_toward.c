#include "types.h"
#include "scroll.h"

// Returns target, limited to within 8 pixels of current.
s32 StepScrollToward(s32 current, s32 target)
{
    if (ABS(current - target) > 8)
    {
        if (target > current)
            target = current + 8;
        else
            target = current - 8;
    }
    return target;
}
