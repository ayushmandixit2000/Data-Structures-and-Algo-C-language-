#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int item;
    struct _dbllistnode *next;
    struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist
{
    int size;
    CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i, cases;
    int numP;
    scanf("%d", &cases);
    for (i = 0; i < cases; i++)
    {
        while (scanf("%d", &item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n", numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value)
{
    // create a new node
    CDblListNode *newNode;
    newNode = (CDblListNode *)malloc(sizeof(CDblListNode));
    newNode->item = value;

    if (ptrCDLL->size == 0) // first node
    {
        newNode->next = newNode;
        newNode->pre = newNode;
        ptrCDLL->head = newNode;
    }
    else
    {
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; // update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
    }
    ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL)
{

    if (CDLL.head == NULL)
        return;

    CDblListNode *temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head)
    {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("%d\n", temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL)
{
    if (ptrCDLL->head == NULL)
        return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next != ptrCDLL->head)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }

    free(cur);
    ptrCDLL->head = NULL;
    ptrCDLL->size = 0;
}

//Since the input is stored as a doubly linked list, we can traverse in both direction for each of the element and count every item that is visible with respective to that element, in both direction.
//To prevent double counting when traversing in both direction, a binary approach will be used 
//This method results in double the amount of pairs we need as it is done with respect to each item
//counter used as bhinary detectors. Stores 1 if a match has been found at a exact place, if not 0
//int counter = 0; //counter increases by 1 after every pair seen


int numMountainPairs(CDblLinkedList CDLL)
{
int count = 0;

int final = 0; //final will be tabulated later
int blocker = 0; //blocker is used to see if middle mountain blocks
int *counter = (int*) calloc(CDLL.size-1, sizeof(int)); 

CDblListNode *first, *second;
first = CDLL.head;

int num1 = 0;
int num2 = 0;
int size = CDLL.size;
if(CDLL.size == 1 || CDLL.size == 0){
    count = 0;
}

else if(CDLL.size == 2){
    count = 1;
}

else{

for(int main = 0; main < size; main ++){
    num1 = first -> item;
    blocker = 0;
    second = first -> next;

    for(int clockwise = 0; clockwise < size - 1; clockwise ++){
        int num3 = 0;
        num2 = second -> item;

        if(num1 < num2){
            num3 = num1;
        }
        else{
            num3 = num2;
        }

        if(num3 >= blocker){
            counter[clockwise] = 1;
        }

        if(blocker < num2){
            blocker = num2;
        }
        second = second -> next;
    }

    second = first -> pre;
    blocker = 0;

    for(int clockwise = size - 2; clockwise > - 1; clockwise --){
        num2 = second -> item;
        int num3 = 0;

        if(counter[clockwise] == 0){
            if(num1 < num2){
                num3 = num1;
            }
            else{
                num3 = num2;
            }

            if(num3 >= blocker){
                counter[clockwise] = 1;
            }
        }
        if(blocker < num2){
            blocker = num2;
        }
        second = second -> pre;

    }

    for (int j = 0; j< size - 1; j++){
        if(counter[j] == 1){
            final++;
            counter[j] = 0;
        }
    }


    first = first -> next;
}

count = final/2;
}

free(counter);
return count;

}