#include <stdlib.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "linkedList.h"

/* intializing a new list */
void CreateList(List *pList){
	pList->head = NULL;
	pList->size = 0;
}


/* adding a node to the end of the list */
void AppendList(List *pList, ListEntry value){
	ListNode *q;
	ListNode *pNode = (ListNode *) malloc(sizeof(ListNode));
	pNode->data = value;
	pNode->next = NULL;
	if(pList->size == 0){
		pList->head = pNode;
	}
	else{
		q = pList->head;
		while(q->next != NULL){
			q = q->next;
		}
		q->next = pNode; 
	}
	pList->size++;
}

/* visit all the nodes of the list passing each entry to a user-defined function */
void TraverseList(List *pList, void(*visit)(ListEntry*)){
	ListNode *p = pList->head;
	while(p){
		(*visit)(&(p->data));
		p=p->next;
	}
}

/* retrieve the node of a specific position in the list*/
void RetrieveList(List *pList, u32 pos, ListEntry *pe){
	u32 i; 
	ListNode *q;
	for(i = 0, q = pList->head; i<pos; i++){
		q = q->next;
	}
	*pe = q->data;
}


void ReplaceList(List *pList, u32 pos, ListEntry e){
	u32 i;
	ListNode *q;
	for(i = 0, q = pList->head; i<pos; i++){
		q = q->next;
	}
	q->data = e;
}



/*

void displayAccount(ListEntry *e){
	printf("Account ID: %d\n", e->accountID);
	printf("Password:   %d\n", e->password);
}



void main(void){
	List testList;
	ListEntry entryToDisplay;
	CreateList(&testList);
	ListEntry admin1 = {7,9};
	AppendList(&testList, admin1);
	ListEntry admin2 = {6,8};
	AppendList(&testList, admin2);
	TraverseList(&testList, &displayAccount);
	RetrieveList(&testList, 0, &entryToDisplay);
	displayAccount(&entryToDisplay);
	
	


}
*/
