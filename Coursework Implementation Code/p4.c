//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
2016/17 S1
Author and Lab Group: HTET NAING / FSP 7
Program name: FSP7_Htet Naing
Date:  November 10,2016
Purpose: Implementing the required functions for Assignment 1 (Question 4)*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode {
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode {
	BSTNode *item;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

		///////////////////////// function prototypes ////////////////////////////////////

		// This is for question 4. You should not change the prototypes of these functions
void insertBSTNode(BSTNode **node, int value);
void printPostOrderIterative(BSTNode *root);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode * pop(Stack *s);
BSTNode * peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	c = 1;
	root = NULL;

	printf("1:Insert an integer into the binary search tree;\n");
	printf("2:Print the post-order traversal of the binary search tree;\n");
	printf("0:Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			printPostOrderIterative(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value) {
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

//The function below aims to print the items in a Binary Search Tree in post-order manner by using iterative method with two stacks. 

void printPostOrderIterative(BSTNode *root)
{	
	//Two stacks are created to store the nodes while traversing the binary search tree.
	Stack a;								
	Stack b; 
	//Initially, the top pointers of the two new stacks are set to NULL;
	a.top =  NULL;							
	b.top =  NULL;
	//temp is used as the temporary pointer to store the current node.
	BSTNode *temp = NULL;

	//First, the root node is pushed to Stack a.
	push(&a, root);							
	while (!isEmpty(&a)){
		//Then it is popped and assigned to temp.
		temp = pop(&a);
		//Next, temp is pushed to Stack b.
		push(&b, temp);					
		//Now Stack a is empty and Stack b is holding the root node pushed by temp.
		//After that, the program checks if the current root node has any left or right child.

		if (temp->left != NULL) {	
		//If it has any of them, they are pushed to stack a.
			push(&a, temp->left);			
		}
		if (temp->right != NULL) {
			push(&a, temp->right);			
		//Now Stack a is holding the child/children of the current root node.
		}									
	//The above procedure repeats until the stack a is empty (i.e. until when there are no more nodes to traverse in the tree).
	}
	//At this stage, Stack a is empty and Stack b has all the nodes arranged in post-order traversal manner (top to bottom).

	while (!isEmpty(&b)) {
		//Now, the top item(node) in Stack b is popped to temp.
		temp = pop(&b);		
		//The item in the temp node is then printed out.
		printf("%d ", temp->item);		
	//The above procedure repeats until the stack b is empty.
	}	
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->item = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode* pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->item;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode* peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->item;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}