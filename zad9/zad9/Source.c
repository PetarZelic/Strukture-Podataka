#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node Node;
typedef Node* position;
struct node {
	int element;
	position left;
	position right;

};
position addNode( position root, int newValue);
int replaceTree(position root);
int inorder(position root, FILE* fp);

int main() {
	position root = NULL;
	position randRoot = NULL;
	
	root = addNode(root, 2);
	addNode(root, 5);
	addNode(root, 7);
	addNode(root, 8);
	addNode(root, 11);
	addNode(root, 1);
	addNode(root, 4);
	addNode(root, 2);
	addNode(root, 3);
	addNode(root, 7);

	FILE* fp = NULL;
	fp = fopen("dat.txt", "w");

	inorder(root,fp);

	replaceTree(root);
	fprintf(fp,"\n");
	inorder(root,fp);

	int x = 0;
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		x = rand() % 81 + 10;
		randRoot = addNode(randRoot, x);
	}
	fprintf(fp,"\n");
	inorder(randRoot,fp);


	fclose(fp);
	return 0;
}


position addNode(position root, int newValue) {
	if (root == NULL) {
		root = (position)malloc(sizeof(Node));

		if (root == NULL) {
			printf("ERROR alocating memory");
			return NULL;
		}
		root->element = newValue;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if (newValue>=root->element) {
			root->left = addNode(root->left, newValue);
		}
		else {
			root->right = addNode(root->right, newValue);
		}
	}
	return root;

}

int replaceTree(position root) {
	if (root == NULL)
		return 0;

	int leftValue = replaceTree(root->left);
	int rightValue = replaceTree(root->right);

	
	int originalValue = root->element;

	root->element = leftValue + rightValue;

	return originalValue + root->element;

}
int inorder(position root,FILE* fp) {

	

	if (root) {
		inorder(root->left,fp);
		fprintf(fp, "%d ", root->element);
		inorder(root->right,fp);
	}
	
	return EXIT_SUCCESS;
}