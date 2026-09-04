#include "mem.h"

// Unlinks node from wherever it sits in the list headed by listHead:
// patches *listHead if node was first, patches both neighbors, clears
// node's own pNext/pPrev.
void List_Remove(ListNode **listHead, ListNode *node)
{
    if (*listHead == node) {
        *listHead = node->pNext;
    }

    if (node->pNext != NULL) {
        node->pNext->pPrev = node->pPrev;
    }

    if (node->pPrev != NULL) {
        node->pPrev->pNext = node->pNext;
    }

    node->pNext = NULL;
    node->pPrev = NULL;
}
