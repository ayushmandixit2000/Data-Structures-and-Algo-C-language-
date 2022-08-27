
#include <stdio.h>
#include <stdlib.h>
 
// Creating  structure

typedef struct node{
int item; struct node *next;
} ListNode;

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




int main(){
ListNode *head = NULL, *temp;
int i = 0;
while (scanf("%d", &i)){
if (head == NULL){
head = malloc(sizeof(ListNode));
temp = head;
}
else{
temp->next = malloc(sizeof(ListNode));
temp = temp->next;
}
temp->item = i;
}
temp->next = NULL;
return 0;
free(temp);
free(head);
}