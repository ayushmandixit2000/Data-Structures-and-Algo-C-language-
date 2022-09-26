#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000 // The size of the array

enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _stackNode
{
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList(LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    // printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c", infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item);
        else
            printf(" %c ", (char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type)
{
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr)
{
    if (LLPtr == NULL || LLPtr->size == 0)
    {
        return 0;
    }
    else
    {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;

        free(temp);
        LLPtr->size--;
        return 1;
    }
}

int isEmptyLinkedList(LinkedList ll)
{
    if (ll.size == 0)
        return 1;
    else
        return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
    while (deleteNode(LLPtr))
        ;
}

void push(Stack *sPtr, char item)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

char peek(Stack s)
{
    return s.head->item;
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

int precedence(char op){ 
    if (op == '*' || op == '/') 
        return 1; 
    else return 0; 
} 

void in2PreLL(char *infix, LinkedList *inExpLL)
{

    // sending int and operators to pointers

    LinkedList first;
    first.head = NULL;
    first.size = 0;
    char * test = infix;

    int length = strlen(infix);
    int count1 = 0;



    for (int i=0; i<length; i++){ 

        if (infix[i] == ' '){ 
            continue;
        }

        else if(infix[i] == '('){
            test[count1] = ')';
            count1++;
        }

        else if(infix[i] == ')'){
            test[count1] = '(';
            count1++;
        }

        else{
            test[count1] = infix[i];
            count1++;
        }
    }

    infix = test;
    infix[count1] = '\0';

    //printf("%s\n" , infix);

    int length1 = strlen(infix);

 

    Stack S;
    S.head = NULL;
    S.size = 0;

    int tot = 0;
    char c;
    int num = 1;

    //while(cur!= NULL){
    for(int i = strlen(infix) - 1; i>=0; i--){
        if(infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')'){
            c = infix[i];
            tot = tot + (c - '0')*num; 
            num *= 10; 
            if (!isdigit(infix[i-1])){ 
                insertNode(inExpLL, tot, OPERAND); 
                tot = 0; 
                num = 1; 
            } 
        }

        else if(infix[i] == ')'){
            while (peek(S) != '(' && S.size > 0){
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
            }
            pop(&S);
        }

        else if(infix[i] == '('){    
            push(&S, infix[i]);
        }

        else{
            while(S.size > 0 && peek(S) != '(' && precedence(peek(S)) > precedence(infix[i]) ){
                //if(precedence(peek(S)) > precedence(cur->item)){ //peek(S) == '*' && cur->item == '-' || peek(S) == '*' && cur->item == '+' || peek(S) == '/' && cur->item == '-' || peek(S) == '/' && cur->item == '+'){ //|| peek(S) == '-' && infix[i] == '-' || peek(S) == '-' && infix[i] == '+' || peek(S) == '+' && infix[i] == '+' || peek(S) == '+' && infix[i] == '-'){ //if peek(S) is times or divide its precedence will be higher regardless
                insertNode(inExpLL, peek(S), OPT);
                pop(&S);
                }
            push(&S, infix[i]);
            }

        }




while(S.size>0){ //empty out stack
    insertNode(inExpLL, peek(S), OPT);
    pop(&S);
}
}




