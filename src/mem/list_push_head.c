#include "mem.h"

void List_PushHead(ListNode **listHead, ListNode *node)
{
    ListNode *pOldHead = *listHead;

    node->pNext = pOldHead;
    node->pPrev = NULL;

    if (pOldHead != NULL) {
        pOldHead->pPrev = node;
    }

    *listHead = node;
}
