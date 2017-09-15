//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
2016/17 S1
Author and Lab Group: HTET NAING / FSP 7 
Program name: FSP7_Htet Naing
Date:  November 10,2016
Purpose: Implementing the required functions for Assignment 1 (Question 2)*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


						//////////////////////// function prototypes /////////////////////////////////////

						// This is for question 2. You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

// You may use the following functions or you may write your own
int insertSortedLL(LinkedList *ll, int item);
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Moves all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i); // You may use question1 function or code this function
			printf("The resulting Linked List is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting Linked List after moving odd integers to the back of the Linked List is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// The function below aims to move all the odd items in a linkedlist to the back and the even items, to the front. 

void moveOddItemsToBack(LinkedList *ll)
{
	//temp pointer is used to traverse the nodes in each linkedlist.
	ListNode *temp = ll->head;
	//even linkedlist and odd linkedlist are used to store even and odd items respectively.
	LinkedList evenList, oddList;
	//Initially, the sizes and head pointers of the above two linkedlists are set to 0 and NULL respectively.
	evenList.size = oddList.size = 0;								
	evenList.head = oddList.head = NULL;

	while (temp != NULL) {	
		//First all the items in the current linkedlist are checked if they are odd or even.
		if (temp->item % 2 == 0) {
			//Even items are added to evenList and odd items, to oddList accordingly.
			insertNode(&evenList, evenList.size, temp->item);		
		}
		else {
			insertNode(&oddList, oddList.size, temp->item);
		}
		temp = temp->next;
	}
	//After that, all items in the current linkedlist are removed.
	removeAllItems(ll);												
	temp = evenList.head;
	while (temp != NULL) {	
		//Next, even items are added to the empty linkedlist first.
		//When adding new items, "size" variable of the respective linkedlist is used as the index positions.
		insertNode(ll, ll->size, temp->item);																						
		temp = temp->next;											
	}

	temp = oddList.head;
	while (temp != NULL) {			
		//After adding even items, odd items are added back to the linkedlist.
		insertNode(ll, ll->size, temp->item);
		temp = temp->next;
	}
}

int insertSortedLL(LinkedList *ll, int item)
{
	int i, j, sameNumber;
	i = j = sameNumber = 0;
	ListNode *ptr = ll->head;

	if (ll->size == 0) {
		insertNode(ll, j, item);
	}
	else {
		while (ptr != NULL) {
			if (item > ptr->item) {
				j = i + 1;
			}
			else if (item == ptr->item) {
				j = -1;
				sameNumber = 1;
			}
			ptr = ptr->next;
			i++;
		}
		if (!sameNumber) {
			insertNode(ll, j, item);
		}
	}
	return j;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll) {

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index) {

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0) {
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value) {

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0) {
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL) {
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index) {

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0) {
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL) {

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
