#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);
int sizeList(ListNode *head);
ListNode *simplereverse (ListNode *head, int k, ListNode *extrapointer, int size);
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

void reverseKNodes(ListNode** head, int K){
ListNode *newhead, *extrapointer;  
ListNode *current = *head;
//get size of linkedlist
int size = sizeList(*head);

//account for behind part

if(K == 0 || K > size){
	extrapointer = NULL;
}
else if(size % K != 0){
	int remainder = size % K;
	int extra_list = size - remainder;

	//split and find pointer for extra list
	int nodenum = 1;
	for (nodenum = 1; nodenum < extra_list; nodenum++){
		current = current -> next;
	}
	extrapointer = current -> next; //extrapointer points to remainders
	current -> next = NULL;

}

else{
extrapointer = NULL;
}

*head = simplereverse(*head, K, extrapointer, size);

}

int sizeList(ListNode *head){
int count = 0;
while (head != NULL){
count++;
head = head->next;
}
return count;
}

ListNode *simplereverse (ListNode *head, int k, ListNode *extrapointer, int size){
ListNode *nextnode, *back, *cur, *firstreversed, *lastreversed, *point;   //declare pointers, back aims to work opposite of next
point = NULL;
firstreversed = NULL;
lastreversed = NULL;

	if (head == NULL || head -> next  == NULL|| k < 2 || k > size){
		return head;
	}

nextnode = head;

while (nextnode != NULL){
	point = nextnode;
	cur = nextnode;
	back = NULL;
	nextnode = cur -> next;

	int count = 1;
	while(nextnode != NULL && count < k ){
	cur -> next = back;
	back = cur;
	cur = nextnode;
	nextnode = nextnode -> next;
	count++;
}

cur -> next = back;

if (firstreversed == NULL){
	firstreversed = cur;
}

if(lastreversed != NULL){
	lastreversed ->next = cur;
}

lastreversed = point;
}

lastreversed -> next = extrapointer;

return firstreversed;
}

