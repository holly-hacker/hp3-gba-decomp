#include "mem.h"

// Zeroes buffer and pushes each stride-byte slot onto a singly-linked
// free list; used to carve fixed-size object pools out of a bulk
// AllocZeroed'd buffer.
void *BuildFreeList(void *buffer, u32 count, s32 stride)
{
    ListNode *listHead;
    u32 i;

    memset(buffer, 0, count * stride);
    listHead = NULL;
    for (i = 0; i < count; i++) {
        List_PushHead(&listHead, (ListNode *)buffer);
        buffer = (u8 *)buffer + stride;
    }
    return listHead;
}
