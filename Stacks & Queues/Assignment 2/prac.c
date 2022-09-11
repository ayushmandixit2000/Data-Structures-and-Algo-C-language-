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

int numMountainPairs(CDblLinkedList CDLL) 
{ 
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail 
    CDblListNode *temp = CDLL.head; 
    CDblListNode *end = CDLL.head->pre; 
    CDblListNode *cur; 
    CDblListNode *b; 
    int count = CDLL.size; 
     
    int num; 
    int lowerNum; 
    if (CDLL.size == 2){ 
        count = 1; 
    } 
    else if (CDLL.size == 1){ 
        count = 0; 
    } 
    else{ 
        while (temp != end->pre){ 
            num = temp->item; 
            b = temp->next->next; 
            while (b != CDLL.head && b != temp->pre){ 
                if (b->item < num){ 
                    lowerNum = b->item; 
                } 
                else{ 
                    lowerNum = num; 
                } 
                int i = 1; 
                int j = 1; 
                cur = temp->next; 
 
                while(cur != b){  
                    if (cur->item > lowerNum){ 
                        i = 0; 
                        break; 
                    } 
                    cur = cur->next; 
                } 
                cur = b->next; 
 
                while (cur != temp){ 
                    if (cur->item > lowerNum){ 
                        j = 0; 
                        break; 
                    } 
                    cur = cur->next; 
                } 
 
                if (i || j){ 
                    ++count; 
                } 
                b = b->next; 
            } 
            temp = temp->next; 
        } 
    } 
    return count; 
}
