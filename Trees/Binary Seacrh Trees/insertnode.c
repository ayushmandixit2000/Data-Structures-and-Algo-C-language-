#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void insertBSTNode(BTNode** cur, int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

int main()
{
    BTNode* root = NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        insertBSTNode(&root, item);
    scanf("%*s");

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    deleteTree(&root);
    root=NULL;
    return 0;
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

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

void insertBSTNode(BTNode** cur, int item){
    BTNode* temp = *cur;
    //Goal of while loop: make the 'temp' pointer point to the parent node of the new node to be inserted (find the place to insert the new node)
    while(temp!=NULL){                  //temp!=NULL----This condition rule out the case where the original tree is empty---> keep on looking for the place to be inserted until it is found!
        if(item < temp->item)          //Case 1: new node should be inserted in the left subtree of the current node!
            if(temp->left==NULL)       // temp->left==NULL----> find the place to insert the item: left child of current node
               break;
            else
               temp = temp->left;       //keep on searching the left subtree of current node
        else if(item > temp->item)     //Case 2: new node should be inserted in the right subtree of the current node!
            if(temp->right==NULL)      // temp->right==NULL----> find the place to insert the item: right child of current node
               break;
            else
               temp = temp->right;     //keep on searching the right subtree of current node
        else{                          //Case 3: item==temp->item: duplicated node appears, no insertion!
           printf("Duplicated Item: %d\n",item);
           return;
        }
    }

    BTNode* node = (BTNode*) malloc(sizeof(BTNode));    //create a new tree node with item
    node->item = item;
    node->left = node->right = NULL;

    //Now insert the node
    if(*cur==NULL)                  //1. insert new node at the root if the original tree is empty
        *cur = node;
    else if(item < temp->item)     //2. insert new node to be the left child of current node
        temp->left = node;
    else                           //3. insert new node to be the right child of current node
        temp->right = node;

    return;
}