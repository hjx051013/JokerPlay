#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "list.h"

DLIST_S *listCreate(FREE_FUNC pfnFree)
{
	DLIST_S *pstDlist;

	if((pstDlist = malloc(sizeof(DLIST_S))) == NULL)
		return NULL;
	pstDlist->head = pstDlist->tail = NULL;
	pstDlist->len = 0;
	pstDlist->free = pfnFree

	return pstDlist;
}

int listAddNodeHead(DLIST_S *pstDlist, void *pVal)
{
	LISTNODE_S *pstNode = NULL;

	if((pstNode = (LISTNODE_S *)malloc(sizeof(LISTNODE_S))) == NULL)
		return OP_ERR;
	pstNode->value = pVal;
	if(pstDlist->len == 0) {
		pstDlist->head = pstDlist->tail = pstNode;
	} else {
		pstNode->next = pstDlist->head;
		pstNode->prev = NULL;
		pstDlist->head->prev = pstNode;
		pstDlist->head = pstNode;
	}
	pstDlist->len++;

	return OP_OK;
}

int lisAddNodeTail(DLIST_S *pstDlist, void *pVal)
{
	LISTNODE_S *pstNode = NULL;

	if((pstNode = (LISTNODE_S *)malloc(sizeof(LISTNODE_S))) == NULL)
		return OP_ERR;
	pstNode->value = pVal;
	if(pstDlist->len == 0) {
		pstDlist->head = pstDlist->tail = pstNode;
	} else {
		pstNode->next = NULL;
		pstNode->prev = pstDlist->tail;
		pstDlist->tail->next = pstNode;
		pstDlist->tail = pstNode;
	}
	pstDlist->len++;

	return OP_OK;
}

void listDelNode(DLIST_S *pstDlist, LISTNODE_S *pstNode)
{
	if(pstNode->prev)
		pstNode->prev->next = pstNode->next;
	else
		pstDlist->head = pstNode->next;
	if(pstNode->next)
		pstNode->next->prev = pstNode->prev;
	else
		pstDlist->tail = pstNode->prev;
	if (pstDlist->free) pstDlist->free(pstNode->value);
	free(pstNode);
	pstDlist->len--;
}
void listEmpty(DLIST_S *pstDlist)
{
	LISTNODE_S *pstCur = pstDlist->head;
	LISTNODE_S *pstNext;
	uint32 len = pstDlist->len;

	while(len--) {
		pstNext = pstCur->next;
		if(pstDlist->free) pstDlist->free(pstCur->value);
		free(pstCur);
		pstCur = pstNext;
	};
	pstDlist->len = 0;
	pstDlist->head = pstDlist->tail = NULL;
}

void listFree(DLIST_S *pstDlist)
{
	listEmpty(pstDlist);
	free(pstDlist);
}

LISTNODE_S *listNodeIndex(DLIST_S *pstDlist, uint32 index)
{
	uint32 i = 0;
	LISTNODE_S *pstCur = pstDlist->head;

	while(i < index) {
		if(pstCur) pstCur = pstCur->next;
		else return NULL;
		i++;
	}

	return pstCur;
}
/*
struct Student {
	char name[64];
	char password[32];
};

int main(void) {
	char name[64];
	char password[32];
	struct Student *tmpStudent = NULL;
	int i, len;
	LISTNODE_S *tmpNode;

	DLIST_S *dlist = listCreate(free);
	FILE *fp = fopen("/home/h50001839/codes/test.txt","rb");
	while(fscanf(fp, "%s%s", name, password) != EOF) {
		tmpStudent = (struct Student *)malloc(sizeof(struct Student));
		strcpy(tmpStudent->name,name);
		strcpy(tmpStudent->password, password);
		listAddNodeHead(dlist, tmpStudent);
	}

	len = listLength(dlist);
	for (i = 0; i < len; i++) {
		tmpNode = listNodeIndex(dlist, i);
		tmpStudent = (struct Student *)tmpNode->value;
		printf("%s, %s\n", tmpStudent->name, tmpStudent->password);
	}

	listEmpty(dlist);
	printf("listLen = %d\n", listLength(dlist));

	return 0;
}
*/
