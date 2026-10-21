#pragma once

#include "types.h"

// Generic intrusive doubly-linked-list node: List_PushHead's `node`
// argument must point at one of these.
typedef struct ListNode {
    struct ListNode *pNext;
    struct ListNode *pPrev;
} ListNode;

void *BuildFreeList(void *buffer, u32 count, s32 stride);
void *AllocObjectFromFreeList(ListNode **freeListHead, ListNode **activeListHead, u32 size);
void List_MoveToHead(ListNode **destListHead, ListNode **srcListHead, ListNode *node);
ListNode *List_PopHead(ListNode **listHead);
void List_PushHead(ListNode **listHead, ListNode *node);
void List_Remove(ListNode **listHead, ListNode *node);
