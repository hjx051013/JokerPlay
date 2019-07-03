#ifndef __LIST_H__
#define __LIST_H__
#include "basic.h"

typedef struct tagListNode {
	struct tagListNode *prev;
	struct tagListNode *next;
	void *value;
} LISTNODE_S;
typedef struct tagDlinkedList {
	LISTNODE_S *head;
	LISTNODE_S *tail;
	void (*free)(void *ptr);
	uint32 len;
} DLIST_S;

#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLasst(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetFreeMethod(l,m) ((l)->free = (m))
#define listGetFree(l) ((l)->free)


DLIST_S *listCreate(void);
int listAddNodeHead(DLIST_S *pstDlist, void *pVal);
int lisAddNodeTail(DLIST_S *pstDlist, void *pVal);
void listDelNode(DLIST_S *pstDlist, LISTNODE_S *pstNode);
void listEmpty(DLIST_S *pstDlist);
void listFree(DLIST_S *pstDlist);
LISTNODE_S *listNodeIndex(DLIST_S *pstDlist, uint32 index);

#endif
