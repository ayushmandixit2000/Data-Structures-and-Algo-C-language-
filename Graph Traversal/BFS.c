#include <stdio.h>
#include <stdlib.h>


typedef struct _listnode //listnode has attributes vertex and a next pointer
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{ //graph has attributes Vertex, edges, visited? and matrix
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode; //normal queue

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

// void BFS (Graph G, int v);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
int BFS(Graph g);
int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

    g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for BFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    //BFS(g,i);
    printf("%d", BFS(g));
    return BFS(g);

}

// void BFS(Graph g, int v){
//     // Write your code here
    
//     // Queue q;
//     // q.head = NULL;
//     // q.tail = NULL;
//     // q.size = 0;

//     // int w;
//     // int i;


//     // enqueue(&q, v);
//     // g.visited[v-1] =  1;
//     // printf("%d" , v);

//     // while(q.size > 0){
//     //     w = dequeue(&q);

//     //     for(i = 0; i < g.V; i++){
//     //         if(g.matrix[w-1][i] == 1 && g.visited[i] == 0){
//     //             g.visited[i] = 1;
//     //             printf("%d", i+1);
//     //             enqueue(&q, i+1); //i is a graph matrix indeitfier, i+1 is the actual vertic
//     //         }
//     //     }
//     // }
// }

int BFS(Graph g){
    
    int max = 0;

    for (int v = 0; v < g.V; v++){

    int count = 1;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int w;
    int i;

    enqueue(&q, v+1);
    g.visited[v] =  1;
    //printf("%d" , v);

    while(q.size > 0){
        w = dequeue(&q);
        for(i = 0; i < g.V; i++){
            if(g.matrix[w-1][i] == 1 && g.visited[i] == 0){
                count++;
                g.visited[i] = 1;
                //printf("%d", i+1);
                enqueue(&q, i+1); //i is a graph matrix indeitfier, i+1 is the actual vertic
            }
        }
    }
    max = count > max? count: max;
    }
    return max;
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}