#include <stdio.h>
#include <stdlib.h>
 
// Creating  structure

typedef struct node{
int item;
struct node *next;
} ListNode;

int removeNode(ListNode **ptrhead, int index);
int getCount(ListNode* head);

int main()
{
    ListNode *head = NULL;
    ListNode *temp;
    ListNode *first;
	ListNode *second;

	printf("Enter a list of numbers, terminated by any non-digit characters: \n");
	int i = 0;
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

first = head;

printf("current list: ");
while (first != NULL){
    printf("%d", first -> item);
    first = first -> next;
}

while (1) {
	printf("\n");

	int count = getCount(head);

	printf("\n");
	printf("Enter the Index of the node to be removed: ");

	int index = 0;

	getchar();
	scanf("%d", &index);


	printf("current list: ");
	removeNode(&head, index);
}
	free(temp);
	free(head);


}


int getCount(ListNode* head)
{
    int count = 0;  // Initialize count
    ListNode* current = head;  // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}




int removeNode(ListNode **ptrhead, int index) {
	ListNode *cur, *second;
	int count = getCount(*ptrhead);

	if (index == 0){
		cur = *ptrhead;
		*ptrhead = cur ->next;	
		second = *ptrhead;
		while (second != NULL){
    printf("%d", second -> item);
    second = second -> next;
}
printf("\n");
	return 1;
	}                                                                                                                                                                                                                                                                                                    

	else if (index == count - 1){
		int i;
		cur = *ptrhead;

		for(i = 0; i < index-1;i++){
			cur = cur -> next;
		}
		
		cur->next = NULL;
		second = *ptrhead;
		while (second != NULL){
    printf("%d", second -> item);
    second = second -> next;
}
	return 1;
	}

	else if (index > 0 && index < count - 1){
		int i;
		cur = *ptrhead;

		for(i =0; i < index - 1; i++){
			cur = cur -> next;

		}
		cur -> next = cur -> next -> next;

		second = *ptrhead;
		while (second != NULL){
    printf("%d", second -> item);
    second = second -> next;
}
	return 1;

	}
	else{
		printf("This node cannot be removed");
		return 0;
	}


}
