#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct directory Directory;
typedef  Directory* position_directory;
struct directory {
	char dir_name[50];
	position_directory sub;
	position_directory next;
};

typedef struct stack Stack;
typedef Stack* position_stack;
struct stack
{
	position_directory directory;
	position_stack next;

};

position_directory create_directory(char name[]);
position_directory find_directory(position_directory current, char name[]);
int push(position_stack head, position_directory current_dir);
position_directory pop(position_stack head);
int print_directories(position_directory current_directory);



int main() {
	Directory head = { .dir_name = {0}, .next = NULL, .sub = NULL };
	Stack head_stack = { .directory = NULL, .next = NULL };
	int x = 1;
	int choice;
	position_directory root = create_directory("C:");
	head.next = root;
	position_directory current_directory = root;
	push(&head_stack, current_directory);

	while (x) {
		printf("\nMenu\n");
		printf("1-md (Create Directory)\n");
		printf("2-cd dir (Change Directory)\n");
		printf("3-cd.. (Go Up)\n");
		printf("4-dir (List Contents)\n");
		printf("5-exit\n");

		scanf(" %d", &choice);
		switch(choice){
		case 1:
			char name[50];
			printf("input the name of the new directory:");
			scanf(" %s", name);
			position_directory new_subdirectory=create_directory(name);
			
			new_subdirectory->next = current_directory->sub;
			current_directory->sub = new_subdirectory;
			printf("Directory %s created\n", new_subdirectory->dir_name);
			break;
		case 2:
			char nam[50];
			printf("Input the name of the directory you want to enter\n");
			scanf(" %s", nam);
			current_directory = find_directory(current_directory, nam);
			push(&head_stack, current_directory);
			printf("%s entered",current_directory->dir_name);
			break;
		case 3:
			current_directory = pop(&head_stack);
			printf("\nCurrently in %s\n", current_directory->dir_name);
			break;
		case 4:
			print_directories(current_directory);
			break;
		case 5:
			x = 0;
			break;
		default:
			printf("please input a correct command\n");
			break;
		}
	}


	return 0;
}


position_directory create_directory(char name[]) {
	position_directory new_directory = NULL;
	new_directory = malloc(sizeof(Directory));
	if (!new_directory) {
		printf("error");
		return -1;
	}
	strcpy(new_directory,name);
	new_directory->next = NULL;
	new_directory->sub = NULL;


	return new_directory;
}
position_directory find_directory(position_directory current, char name[]) {
	position_directory subdirectory = current->sub;
	while (subdirectory != NULL) {
		if (strcmp(name, subdirectory->dir_name) == 0)
			return subdirectory;
		else
			subdirectory = subdirectory->next;
	}
	printf("coudlnt find that directory\n");
	return current;
}
int push(position_stack head_stack, position_directory current_directory) {

	position_stack new_element = NULL;
	new_element = malloc(sizeof(Stack));

	if (new_element == NULL) {
		printf("\nERROR alocating memory");
		return 1;
	}

	new_element->directory = current_directory;

	new_element->next = head_stack->next;
	head_stack->next = new_element;

	return 0;
}
position_directory pop(position_stack head_stack) {

	if (head_stack->next == NULL) {
		printf("\nERROR:stack is empty");
		return NULL;
	}

	if (head_stack->next->next == NULL) {
		return head_stack->next->directory;
	}

	position_stack to_delete = head_stack->next;
	head_stack->next = to_delete->next;

	free(to_delete);

	return head_stack->next->directory;
}
int print_directories(position_directory current_directory) {
	position_directory subdirectory = current_directory->sub;

	if (subdirectory == NULL) {
		printf("\nERROR: no directories found in current directory");
		return 1;
	}
	printf("Directories in %s:\n", current_directory->dir_name);
	while (subdirectory != NULL) {
		printf("%s\n", subdirectory->dir_name);
		subdirectory = subdirectory->next;
	}

	return 0;
}

	
