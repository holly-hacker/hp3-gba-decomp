#include "mem.h"

// Pops and returns the head node, fixing up the new head's pPrev and
// clearing the popped node's own pNext.
ListNode *List_PopHead(ListNode **listHead)
{
    ListNode *head = *listHead;

    if (head != NULL) {
        ListNode *next = head->pNext;

        *listHead = next;

        if (next != NULL) {
            next->pPrev = NULL;
        }

        head->pNext = NULL;
    }
    return head;
}
