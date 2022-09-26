#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = (StackNode *) malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void in2Post(char* infix, char* postfix){
Stack S;
S.head = NULL;
S.size = 0;

int length = strlen(infix);
int k = 0;

for(int i = 0; i < length; i++){
    if(infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')'){ // take out numbers and put them in postfix accordingly
        postfix[k] = infix[i];
        k++;
    }

    else if(infix[i] == ')'){  // sends everything from open bracket to close bracket to postfix, since this is more priority
        while (peek(S) != '('){
            postfix[k] = peek(S);
            k++;
            pop(&S);
        }
        pop(&S); //pop out the open bracket from the stack
    }

    else if(infix[i] == '('){ //when there is a open bracket, send it to the stack first and let the programme run until close brakcet is seen and the previous scenario is executed
        push(&S, infix[i]);
    }

    else{
        while(S.size > 0 && peek(S) != '('){
            if(peek(S) == '*' || peek(S) == '/' || peek(S) == '-' && infix[i] == '-' || peek(S) == '-' && infix[i] == '+' || peek(S) == '+' && infix[i] == '+' || peek(S) == '+' && infix[i] == '-'){ //if peek(S) is times or divide its precedence will be higher regardless
                postfix[k] = peek(S);
                k++;
                pop(&S);
            }
            else{
                break;
            }
        }

        push(&S, infix[i]);
    }
}

while(S.size>0){ //empty out stack
    postfix[k] = peek(S);
    k++;
    pop(&S);
}

postfix[k] = 0;

}