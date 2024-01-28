#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Node node;
typedef node* position;
struct Node {
	int value;
	position left;
	position right;
};

position addNewElement(position current,int value);
int printInorder(position current);
int printPostorder(position current);
int printPreorder(position  current);
int printLevelorder(position current);
position findTarget(position current, int targetValue);
position deleteElement(position root, int value);
position minimum(position root);

int main() {
	position root = malloc(sizeof(node));
	if (root == NULL) {
		printf("ERROR alocating memory for root node!\n");
		return 1;
	}
	root->left = NULL;
	root->right = NULL;
	root->value = 0;
	

	int val=1;
	int choice;
	printf("please input the value of the first node\n");
	scanf("%d",&root->value);	
	printf("%d",root->value);
	


	while (val) {
		printf("\nMENU\n");
		printf("1-add new element\n");
		printf("2-print elements\n");
		printf("3-delete element\n");
		printf("4-find element\n");
		printf("5-exit\n");
		printf("please choose a option:\n");
		scanf("%d", &choice);
		int newValue;
		char simbol;
		position target;
		int element = 0;
		switch (choice)		{
		case 1:
			
			printf("input the new value\n");
			scanf("%d",&newValue);
			addNewElement(root, newValue);
			break;
		case 2:
			
			printf("A-inorder\n");
			printf("B-postorder\n");
			printf("C-preorder\n");
			printf("D-levelorder\n");
			printf("please choose printing method\n");
			scanf(" %c", &simbol);
			switch (simbol) {
			case 'A':
				printInorder(root);
				break;
			case 'B':
				printPostorder(root);
				break;
			case 'C':
				printPreorder(root);
				break;
			case 'D':
				printLevelorder(root);
				break;
			}
			break;
		case 3:
			
			printf("Enter the element to delete:");
			scanf("%d", &element);
			deleteElement(root, element);

			break;
		case 4:
			printf("input the value to find\n");
			scanf("%d", &newValue);
			target = findTarget(root, newValue);
			if (target != NULL)
				printf("found target %d", target->value);
			else
				printf("target not found");
			break;
		case 5:
			val = 0;
			printf("exiting menu");
			break;
		default:
			printf("please input a correct choice\n");
			break;
		}

	
	
	}


	return 0;
}

position addNewElement(position current, int value) {

	if (current == NULL) {
		current = (position)malloc(sizeof(node));
		if (current == NULL) {
			printf("ERROR alocating memory for new element!");
			return NULL;
		}
		current->left = NULL;
		current->right = NULL;
		current->value = value;
	}

  	else if (current->value > value) {
		current->left = addNewElement(current->left, value);
	}
	else {
		current->right = addNewElement(current->right, value);
	}
	return current;
}

int printInorder(position current) {
	if (current == NULL)
		return 0;

	printInorder(current->left);
	printf("%d", current->value);
	printInorder(current->right);
	return 1;
}
int printPostorder(position current) {
	if (current == NULL)
		return 0;

	printInorder(current->left);
	printInorder(current->right);
	printf("%d", current->value);
	return 1;
}
int printPreorder(position  current) {
	if (current == NULL)
		return 0;

	printf("%d", current->value);
	printInorder(current->left);
	printInorder(current->right);
	return 1;
}
int printLevelorder(position root) {
	if (root == NULL) {
		return 1;
	}

	position queue[100];
	int front = 0, rear = 0;
	queue[rear++] = root;

	while (front < rear) {
		position current = queue[front++];
		printf("%d ", current->value);

		if (current->left != NULL)
			queue[rear++] = current->left;

		if (current->right != NULL)
			queue[rear++] = current->right;
	}
	return 0;
}

position findTarget(position current, int targetValue) {
	if (current != NULL) {
		if (current->value > targetValue) {
			current = findTarget(current->left, targetValue);
		}
		else if (current->value < targetValue) {
			current = findTarget(current->right, targetValue);
		}

		return current;
	}
	return NULL;
}

position deleteElement(position root, int value)
{
	if (root == NULL) {
		printf("Element not found");
		return NULL;
	}

	if (value < root->value) {
		root->left = deleteElement(root->left, value);
	}
	else if (value > root->value) {
		root->right = deleteElement(root->right, value);
	}
	else if (root->left != NULL && root->right != NULL) {
		position temp = minimum(root->right);
		root->value = temp->value;
		root->right = deleteElement(root->right, root->value);
	}
	else {
		position toDelete = root;
		if (root->left == NULL) {
			root = root->right;
		}
		else {
			root = root->left;
		}
		free(toDelete);
	}

	return root;
}
position minimum(position root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}
