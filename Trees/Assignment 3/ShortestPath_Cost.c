#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}
int findparent(BTNode* root, int num);


int findparent(BTNode* root, int num){
    Queue q;
    q.head = NULL;
    q.tail = 0;
    q.size = 0;
    BTNode *node = NULL;
    int num1 = -1; //return negaitve 1 when head is sent as num;

    if(root){
        enqueue(&q,root);
        while(q.size>0){
            node = getFront(q);
            dequeue(&q);

            if(node -> left){
                if(node -> left -> nodeV == num){
                    num1 = node -> nodeV;
                    return num1;
                }
            }

            if(node -> right){
                if(node -> right -> nodeV == num){
                    num1 = node -> nodeV;
                    return num1;
                }
            }

            if(node -> left) enqueue(&q, node -> left);
            if(node -> right) enqueue(&q, node -> right);
        }
    }
    return num1;
}


int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{

if(nodeV1 = nodeV2){
    return nodeV1;
}
int *path1 = (int*)malloc(sizeof(*path1)); //store path of nodev1
int size1 = 0;
int *path2 = (int*)malloc(sizeof(*path2)); //store path of nodev1
int size2 = 0;

path1[0] = nodeV1;
size1++;
int num = 0;
int i = 1;
while (num != -1){
    num = findparent(node, nodeV1);
    if(num == -1){
        break;
    }
    path1[i] = num;
    i++;
    size1++;
    nodeV1 = num;
}

path2[0] = nodeV2;
size2++;
int num1 = 0;
int i1 = 1;
while (num1 != -1){
    num1 = findparent(node, nodeV2);
    if(num1 == -1){
        break;
    }
    path2[i1] = num1;
    size2++;
    i1++;
    nodeV2 = num1;
}

int temp = 0;
while (1){
    if(path1[size1 - 1] == path2 [size2 - 1]){
        temp = path1[size1 - 1];
        path1[size1 - 1] = '\0';
        size1--;
        path2[size2 - 1] = '\0';
        size2--;
    }

    else{
        break;
    }
}

int total = temp;

int index1 = 0;
while(path2[index1] != '\0'){
    total = total + path2[index1];
    index1 ++;
}

int index2 = 0;
while(path1[index2] != '\0'){
    total = total + path1[index2];
    index2 ++;
}

return total;
}