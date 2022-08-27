#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

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


	triPartition(&head, pivot);
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

void triPartition(ListNode** head, int pivot){
ListNode *cur, *newhead, *firstend, *secondstart, *secondend, *thirdstart, *first, *second, *third, *thirdend ;

newhead = firstend = secondstart = thirdend = secondend = thirdstart = NULL;

cur = *head;

while (cur != NULL){

if (cur -> item < pivot){
    
    if (newhead == NULL){
        newhead = cur;
        first = cur;
    }
    else{
        first -> next = cur;
        first = cur;
    }
}

else if (cur -> item == pivot){
    if (secondstart == NULL){
        secondstart = cur;
        second = cur;
    }
    else{
        second -> next = cur;
        second = cur;
    }
}

else if (cur -> item > pivot){
    if (thirdstart == NULL){
        thirdstart = cur;
        third = cur;
    }
    else{
        third -> next = cur;
        third = cur;
    }
}

cur = cur -> next;

}

firstend = first;
secondend = second;
thirdend = third;

thirdend -> next = NULL;
if (firstend != NULL && secondstart != NULL){
    firstend -> next = secondstart;
}

else if (firstend != NULL && secondstart == NULL && thirdstart != NULL){
    firstend -> next = thirdstart;
}

else if (newhead == NULL && secondstart != NULL){
    newhead = secondstart;
}

else if (newhead == NULL && secondstart == NULL && thirdstart != NULL){
    newhead = thirdstart;
}


if (secondend != NULL && thirdstart != NULL){
    secondend -> next = thirdstart;
}


*head = newhead;

}

