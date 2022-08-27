#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);
int sizeList(ListNode *head);
int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

ListNode *reverseSegment(ListNode* head, int start, int end)
{
ListNode *firstend, *beforerhead, *afterrhead, *cur, *endhead, *nextnode, *back;
int size = sizeList(head);
if(start == end || end < start || start < 0 || end > size - 1 ){
    return head;
}
back = NULL;
cur = head;
int count = 1;
for (count = 1; count < start; count ++){
    cur = cur -> next;
}
firstend = cur;
beforerhead = cur -> next;


if(start == 0 ){
    beforerhead = firstend;
}

cur = head;
int count1 = 0;
for (count1 = 0; count1 < end; count1 ++){
    cur = cur -> next;
}
afterrhead = cur;
endhead = afterrhead -> next;

afterrhead -> next = NULL;

cur = beforerhead;

while( cur != NULL){
    nextnode = cur -> next;
    cur -> next = back;
    back = cur;
    cur = nextnode;
}

if(start == 0){
    beforerhead -> next = endhead;
    head = afterrhead;
    return head;
}

firstend -> next = afterrhead;
beforerhead -> next = endhead;

return head;
}


int sizeList(ListNode *head){
int count = 0;
while (head != NULL){
count++;
head = head->next;
}
return count;
}