#include "actor.h"
#include "oam.h"
#include "interrupts.h"

// Frees every actor on the active list, then clears leftover sprites from OAM and waits
// for VBlank so the empty screen is displayed. Game modes call this on exit.
void FreeAllActors(ListNode **activeListHead)
{
    ListNode *node = *activeListHead;
    ListNode *next;

    while (node != NULL)
    {
        next = node->pNext;
        FreeActor((Actor *)node);
        node = next;
    }

    HideUnusedOamEntries();
    WaitForVBlankIntr();
}
