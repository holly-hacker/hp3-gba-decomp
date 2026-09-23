#include "types.h"
#include "mem.h"
#include "object.h"
#include "oam.h"
#include "vblank.h"

// Frees every object on the active list, then clears leftover sprites from OAM and waits
// for VBlank so the empty screen is displayed. Game modes call this on exit.
void FreeAllObjects(ListNode **activeListHead)
{
    ListNode *node = *activeListHead;
    ListNode *next;

    while (node != NULL)
    {
        next = node->pNext;
        FreeObject((Object *)node);
        node = next;
    }

    HideUnusedOamEntries();
    WaitForVBlankIntr();
}
