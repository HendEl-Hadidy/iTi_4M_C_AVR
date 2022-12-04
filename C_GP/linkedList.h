#ifndef LINKED_LIST_PRIVATE_H
#define LINKED_LIST_PRIVATE_H


/********** Configurable list entery data type	*************/

/*
typedef struct listEntry{
	u32 accountID;
	u32 password;
	
}ListEntry;
*/



typedef struct listEntry{
	
	u8 fullName[50];
	u8 fullAddress[50];
	u8 nationalID[15];
	u8 age;
	u8 guardianName[50];
	u8 guardianNationalID[15];
	u8 accountStatus;
	u32 accountID;
	u32 password;
	f64 balance;
	
}ListEntry;



/***************** linked list structure ********************/

typedef struct listNode{
	ListEntry data;
	struct listNode *next;
}ListNode;


typedef struct list{
	ListNode *head;
	u32 size;
}List;

/************** Fun Prototypes *************/
void CreateList(List *pList);
void AppendList(List *pList, ListEntry value);
void TraverseList(List *pList, void(*visit)(ListEntry*));
void RetrieveList(List *pList, u32 pos, ListEntry *pe);
void ReplaceList(List *pList, u32 pos, ListEntry e);

#endif  