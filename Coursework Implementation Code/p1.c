//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
2016/17 S1
Author and Lab Group: HTET NAING / FSP 7
Program name: FSP7_Htet Naing
Date:  November 10,2016
Purpose: Implementing the required functions for Assignment 1 (Question 1)*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode {
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode				

typedef struct _linkedlist {
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


						///////////////////////// function prototypes ////////////////////////////////////

						// This is for question 1. You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

// You may use the following functions or you may write your own
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
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
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

/*	The function below aims to sort the items in the linkedlist in the ascending order.
	Whenever a new item is added, it will be inserted at the suitable place to maintain the ascending order.
	If the insertion succeeds, the function returns the index position of the new node that is added.
	Otherise it returns -1. */

int insertSortedLL(LinkedList *ll, int item)
{
	//i and j are used to keep track of the current node and the index position of the new item in the linkedlist respectively.
	int i, j, sameNumber;
	//sameNumber is used to check if the new item has the same value as the existing item. Initially set to 0.
	i = j = sameNumber = 0;	
	//ptr is the temporary pointer used to traverse nodes in the linkedlist.
	ListNode *ptr = ll->head;						
	//First the program checks whether the size of the linked list is zero.
	if (ll->size == 0) {		
		//If it is zero, the first node is inserted at index 0.
		insertNode(ll, j, item);					
	}
	else {				
		//Otherwise, the new item is compared against all the existing items.
		//It can be done by traversing existing nodes in the linkedlist using the temporary pointer(ptr).
		while (ptr != NULL) {					
			//If the new item is greater than current item, the current index+1 is assigned to j	
			//(because the bigger number should come after the current index number).
			if (item > ptr->item) {					
				j = i + 1;					
			}				
			//If the new item is similar to one of the existing items, sameNumber is set to 1 and j to -1.
			else if (item == ptr->item) {		
				j = -1;
				sameNumber = 1;
			}
			ptr = ptr->next;
			i++;
		}
		//the new item will be added only if the sameNumber is not set to 1. 
		if (!sameNumber) {						
			insertNode(ll, j, item);
		}
	}
	//The function returns j value which represents the index position of the new node.
	return j;										
}



///////////////////////////////////////////////////////////////////////////////////

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