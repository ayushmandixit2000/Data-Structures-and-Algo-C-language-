#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char*);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    scanf("%[^\n]%*c",postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}

void push(Stack *sPtr, double item){
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

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

double exePostfix(char* postfix)
{
Stack s;
s.head = NULL;
s.size = 0;
 
// push first two to stack first
int length = strlen(postfix);


if(length>2){
    if(postfix[0] == '+' || postfix[0] == '-' || postfix[0] == '*' || postfix[0] == '/' || postfix[1] == '+' || postfix[1] == '-' || postfix[1] == '*' || postfix[1] == '/'){
        printf("syntax error");
        return 0;
    }
    else{
        char x = postfix[0]; //converting char to double
        char *str = &x;
        double ax = atof(str);
        push(&s, ax);
        char y = postfix[1];
        char *str1 = &y;
        double ay = atof(str1);
        push(&s, ay);
    }
}
else{
    printf("syntax error");
    return 0;
}

int i = 0;
double result = 0;

for(i = 2;i < length; i++){
    if(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/'){
        double second = peek(s);
        pop(&s);
        double first = peek(s);
        pop(&s);

        if(postfix[i] == '+'){
        result = second + first;
        }
        else if(postfix[i] == '-'){
        result = first - second;
        }
        else if(postfix[i] == '*'){
        result = first * second;
        }
        else if(postfix[i] == '/'){
        result = first / second;
        }
        push(&s, result);
    }

    else{
        //double aei = postfix[i];
        char ae = postfix[i];
        char *str1 = &ae;
        double ay1 = atof(str1);
        push(&s, ay1);
    }
}

return result;






}