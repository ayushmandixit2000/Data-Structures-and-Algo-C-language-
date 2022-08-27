#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	reverseKNodes(&head, K);
	printList(head);
    deleteList(&head);
	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}
void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

ListNode *findNode(ListNode *cur, int index) {
	
	if (!cur || index<0) {
		return NULL;
	}

	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}

	return cur;
}

ListNode *reverseSegment(ListNode* head, int start, int end)
{
	ListNode *startNode,*endNode,*endNextNode,*beforeStartNode;
	ListNode *cur = head;

	int size=0;
	while (cur) {
		cur=cur->next;
		size++;
	}

	if (start < 0 || start > size || end < 0 || end > size || end < start) {
		return head;
	}

	cur = head;
	startNode = findNode(cur, start);
	endNode = findNode(cur, end);
	beforeStartNode = findNode(cur, start-1);
	endNextNode = findNode(cur, end+1);

	endNextNode = endNode->next;
	endNode->next = NULL;

	cur = startNode;
	ListNode *pre,*next = NULL;
	while (cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	endNode = pre;

	if (beforeStartNode != NULL) {
		beforeStartNode->next = endNode;
	} else {
		head = endNode;
	}

	startNode->next = endNextNode;
	return head;
// Write your code here
}

int getIndex(ListNode *head, ListNode *cur) {
	int index=0;
	ListNode *tracker = head;

	if (cur == head) {
		return 0;
	}
	while (tracker != cur) {
		tracker = tracker->next;
		index++;
	}

	return index-1;
}


void reverseKNodes (ListNode **head, int K) {
	ListNode *cur = *head;
	ListNode *startNode = *head;
	ListNode *prevNode;
	int start, end;

	int size=0;

	while(cur!=NULL) {
		cur=cur->next;
		size++;
	}

	// printf("size: %d \n",size);
	cur=*head;

	for (int i=0; i<size;i++) {
		if (K == 0 || K >= size || cur == NULL) {
			break;
		}
		if(i%K == 0 && i != 0) {
			if (i==K) {
				startNode = *head;
			} else {
				startNode = prevNode->next;
			}
			
			start = getIndex(*head, startNode);
			end = getIndex(*head, cur);
			*head = reverseSegment(*head, start, end);
			prevNode = cur;
		}
		cur = cur->next;
		// printf("i: %d \n",i);
	}
}