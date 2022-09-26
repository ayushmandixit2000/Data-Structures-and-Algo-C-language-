#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

enum ExpType {OPT,OPERAND};

typedef struct _queueNode
{
    int item;
    enum ExpType type;
    struct _queueNode *next;
}QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

void enqueue (Queue *qptr, int item, enum ExpType type);
int dequeue(Queue *qPtr);
QueueNode* getFront(Queue q);
int isEmptyQueue(Queue q);

void expressionQ(char *infix, Queue* qPtr);
void printExpQ(Queue* qPtr);

int main()
{
    char infix[SIZE];
    scanf("%[^\n]%*c",infix);

    Queue inExpQ;
    inExpQ.head = NULL;
    inExpQ.tail = NULL;
    inExpQ.size = 0;

    expressionQ(infix,&inExpQ);
    printf("Output:\n");
    printExpQ(&inExpQ);

    return 0;
}

void enqueue (Queue *qPtr, int item, enum ExpType type)
{
    QueueNode *newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->type = type;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail =newNode;
    qPtr->size++;

}
int dequeue(Queue *qPtr)
{
    if(qPtr == NULL || qPtr->head ==NULL)
        return 0;
    else{
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;

        if(qPtr->head == NULL)
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

QueueNode* getFront(Queue q)
{
    return q.head;
}

int isEmptyQueue(Queue q){
   if(q.size==0) return 1;
    else return 0;
}

void printExpQ(Queue *qPtr){
    if(qPtr==NULL) return;

    QueueNode* temp = NULL;
    temp = getFront(*qPtr);

    while(temp!=NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        dequeue(qPtr);
        temp = getFront(*qPtr);
    }
    printf("\n");

}


void expressionQ(char *infix, Queue* qPtr)
{
Queue helperq; //queue to be used for storing
helperq.head = NULL;
helperq.tail = NULL;
helperq.size = 0;
int brack = 0;

int length = strlen(infix);
for(int i = 0; i < length; i++){

    //if not an operator, send it to helperq
    if(infix[i] != '*' && infix[i] != '/' && infix[i] != '+' && infix[i] != '-' && infix[i] != '(' && infix[i] != ')' && infix[i] != '%' ){
        int xz = infix[i] - '0';
        enqueue(&helperq, xz, OPERAND); //enques the number exactly
    }

    else if(brack == 1){
        enqueue(qPtr, infix[i], OPT);
        brack = 0;
    }

    else if(infix[i] == '('){
        enqueue(qPtr, infix[i], OPT);
    }


    else{
        int size = helperq.size;
        if(helperq.size == 1){
            int item1 = helperq.head -> item;
            dequeue(&helperq);
            enqueue(qPtr, item1, OPERAND);
            enqueue(qPtr, infix[i], OPT);
            if(infix[i] == ')'){
                brack = 1;
            }
        }

        else if(helperq.size == 0){
            enqueue(qPtr, infix[i], OPT);
        }


        else{
            char S1[200];
            char S2[200];
            int itemfirst = helperq.head -> item;
            int itemsecond;
            dequeue(&helperq);
            while(helperq.size > 0){
                itemsecond = helperq.head -> item;
                sprintf(S1, "%d", itemfirst);
                sprintf(S2, "%d", itemsecond);
                strcat(S1, S2);
                int final = atoi(S1);
                itemfirst = final;
                S1[0] = 0;
                S2[0] = 0;
                dequeue(&helperq);
            }
            enqueue(qPtr, itemfirst, OPERAND);
            enqueue(qPtr, infix[i], OPT);
            //if the current char in the infix is a ')' store this first for comparison later;
            if(infix[i] == ')'){
                brack = 1;
            }
       
            }
        }

}

char S1[200];
char S2[200];

int itemfirst =0;
int itemsecond = 0;

if(helperq.size>0){
    itemfirst = helperq.head -> item;
    dequeue(&helperq);

    while(helperq.size > 0){
        itemsecond = helperq.head -> item;
        sprintf(S1, "%d", itemfirst);
        sprintf(S2, "%d", itemsecond);
        strcat(S1, S2);
        int final = atoi(S1);
        itemfirst = final;
        S1[0] = 0;
        S2[0] = 0;
        dequeue(&helperq);
    }
    enqueue(qPtr, itemfirst, OPERAND);
}


S1[0] = 0;
S2[0] = 0;

}