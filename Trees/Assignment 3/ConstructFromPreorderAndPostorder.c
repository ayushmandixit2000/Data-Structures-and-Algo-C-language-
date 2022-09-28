#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

void buildTree(BTNode** node, char* preO, char* postO)
{
int length = strlen(preO);

if(*node == NULL){  //if node is not assigned yet, assign it to be head of binary tree, every other node from here will be preassigned below itself
(*node) = (BTNode*) malloc(sizeof(BTNode));
(*node) -> id = preO[0];
}

if(strlen(preO) == 0 || strlen(postO) == 0 || strlen(preO) == 1 || strlen(postO) == 1){ //return if only one or 0 elements are in preO or postO
    return;
    
}
(*node) -> left = (BTNode*) malloc(sizeof(BTNode)); //assign node -> left and right
(*node) -> left -> id = preO[1];
(*node) -> right = (BTNode*) malloc(sizeof(BTNode));
(*node) -> right -> id = postO[length-2];
int index1 = 0;
for(int index0 = 0; index0 < length; index0++){ //find index of new left node's item in post, every item to the left of this wil be the new postO in order. Simialry, every item to the right of the left node's element in preO until the right node element will be the new preO in order
    if(postO[index0] == preO[1]){
        break;
    }
    else{
        index1++;
    }
}
char *new2 = malloc(strlen(preO));
char *new3 = malloc(strlen(postO));
buildTree(&((*node) -> left) , strncpy(new2, preO + 1, index1 + 1), strncpy(new3, postO, index1 + 1)); //indexing new preO and postO
if(postO[length - 2] == preO[1]){ //edge case of only one child identified by seeing if second element and second last element in preO and postO respectively are the same, if that is the case, there is no right child node
    (*node) -> right = NULL;
    return;
}

else{
char *new4 = malloc(strlen(preO));
char *new5 = malloc(strlen(postO));
buildTree(&((*node) -> right) , strncpy(new4, preO + index1 + 2, length - index1 - 2), strncpy(new5, postO + index1 + 1, length - index1 - 2)); //indexing new preO and postO
return;
}
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
// Write your code here
}