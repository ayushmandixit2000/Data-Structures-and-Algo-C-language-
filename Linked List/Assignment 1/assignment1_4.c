#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);
int sizeList(ListNode *head);
int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll){
    ListNode *cur, *firsthead, *secondhead, *firstchange;
    int size = sizeList(ll.head);

    if (size < 3){
        return ll;
    }
    cur = ll.head;
    int count = 1;
    for(count = 1; count < size/2; count ++){
        cur = cur -> next;
    }
    secondhead = cur -> next;
    cur -> next = NULL;
    firsthead = ll.head;

    ll.head = secondhead;
    firstchange = ll.head;
    secondhead = secondhead -> next;

    int counter = 1;
    for(counter = 1; counter < size; counter ++){
        if (counter % 2 != 0){
            firstchange -> next = firsthead;
            firsthead = firsthead -> next;
            firstchange = firstchange -> next;
            firstchange -> next = NULL;
        }
        else {
            firstchange -> next = secondhead;
            secondhead = secondhead -> next;
            firstchange = firstchange -> next;
            firstchange -> next = NULL;
        }
    }

    int count1 = 1;
    cur = ll.head;
    firsthead = secondhead = firstchange = NULL;
    for(count1 = 1; count1 < size/2; count1 ++){
        cur = cur -> next;
    }

    secondhead = cur -> next;
    cur -> next = NULL;
    firsthead = ll.head;

    firstchange = ll.head;
    firsthead = firsthead -> next;

    int counter1 = 1;
    for(counter1 = 1; counter1 < size - 1; counter1 ++){
        if (counter1 % 2 != 0){
            firstchange -> next = secondhead;
            secondhead = secondhead -> next;
            firstchange = firstchange -> next;
            firstchange -> next = NULL;
        }
        else {
            firstchange -> next = firsthead;
            firsthead = firsthead -> next;
            firstchange = firstchange -> next;
            firstchange -> next = NULL;
        }
    }

    if (secondhead -> next == NULL){
        firstchange -> next = secondhead;
    }

    return ll;
}

int sizeList(ListNode *head){
int count = 0;
while (head != NULL){
count++;
head = head->next;
}
return count;
}
