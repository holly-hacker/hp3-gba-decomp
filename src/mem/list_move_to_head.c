#include "mem.h"

// Removes node from the list at srcListHead and pushes it onto the front
// of the list at destListHead -- a requeue/move-to-front across two
// lists (or the same list twice).
void List_MoveToHead(ListNode **destListHead, ListNode **srcListHead, ListNode *node)
{
    List_Remove(srcListHead, node);
    List_PushHead(destListHead, node);
}
