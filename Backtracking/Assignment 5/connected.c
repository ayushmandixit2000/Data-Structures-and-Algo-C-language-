#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

int Connected (Graph);

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
    for(i=0;i<g.V;i++) 
        g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
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
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res ==1)
        printf("The graph is connected.\n");
    else
        printf("The graph is not connected.\n");

    return 0;
}

int Connected (Graph g)
{
    
    Stack s;
    s.head = NULL;
    s.size = 0;

    //for connected we can start from anywhere, let us start with v= 1;

    push(&s, 1);
    g.visited[0] = 1;
    int count = 1;

    while(s.size > 0){
        int w = peek(s);

        int stopnode = 0;

        for(int i = 0; i < g.V; i++){
            if(g.matrix[w-1][i] == 1 && g.visited[i] == 0){
                g.visited[i] = 1;
                count++;
                push(&s, i+1);
                stopnode = 1;
                break;
            }
        }

        if(stopnode == 0){
            pop(&s);
        }
    }
    
    
    if(count == g.V){
        return 1;
    }

    return 0;
    
    //write your code here
    //if the graph is connected, all nodes will be visisted

    // Stack s;
    // s.head = NULL;
    // s.size = 0;
    // int w;
    // int i;

    // int count = 1;

    // int v = 1;

    // push(&s, v);
    // g.visited[v-1] = 1;

    // int stopnode; //to monitor when backtracking will start

    // while(s.size > 0){
    //     w = peek(s);

    //     stopnode = 0;

    //     for(i = 0; i < g.V ; i++){ //when first adjacent with univisited is found we push it
    //         if(g.matrix[w-1][i] == 1 && g.visited[i] == 0){
    //             push(&s, i+1);
    //             count++;
    //             g.visited[i] = 1;
    //             stopnode = 1;
    //             break;
    //         }
    //     }

    //     if(stopnode == 0){
    //         pop(&s);
    //     }
    // }

    // // printf("%d\n", count);
    // if (count == g.V){
    //     return 1;
    // }

    // return 0;
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

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
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

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
