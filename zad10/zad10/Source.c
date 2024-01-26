#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct _town Town;
typedef Town* townPosition;
struct _town {
	char townName[50];
	int population;
	townPosition left;
	townPosition right;
	townPosition next;

};

typedef struct _country Country;
typedef Country* countryPosition;
struct _country {
	char countryName[50];
	countryPosition left;
	countryPosition right;
	countryPosition next;
	townPosition townRootTree;
	Town townListHead;
	
};

struct _hash_table {
	countryPosition buckets[11];
};
typedef struct _hash_table HashTable;

//zadatak pod a)
int ReadFromCountryFile(countryPosition countriesListHead,char* countriesFile);
int AddCountryToList(countryPosition countriesListHead, char* country, char* TownFile);
townPosition ReadTownFileAndAddToTree(townPosition townRoot, char* TownFile);
townPosition AddTownToTree(townPosition townRoot, townPosition NewTown);
int PrintCountryList(countryPosition countryHeadList);
int printTownTree(townPosition townRootTree);
townPosition createNewTown(char* townName, int townPopulation);


//zadatak pod b)
int ReadFromCountryFileAddToTree(countryPosition countriesTreeRoot, char* countriesFile);
countryPosition AddCountryToTree(countryPosition, char* country, char* CountryTownFile);
countryPosition CreateNewCountry(char* country);
int printCountryTree(countryPosition countryRootTree, townPosition townHead);
int ReadTownFileAndAddToList( char* TownFile,countryPosition CountryTreeRoot);
int AddTownTolist(townPosition townHead, townPosition NewTown);
int printTownList(townPosition townHead);

int main() {
	Country CountriesListHead= { .countryName = { 0 },
		.next = NULL,
		.left = NULL,
		.right = NULL,
		.townRootTree = NULL,
		.townListHead = {
			.townName = { 0 },
			.population = 0,
			.next = NULL,
			.left = NULL,
			.right = NULL,
		}
	};
	countryPosition CountryRootTree = NULL;

	ReadFromCountryFile(&CountriesListHead, "drzave.txt");
	PrintCountryList(&CountriesListHead);
	printf("\n-----------------------------------------");
	
	
	ReadFromCountryFileAddToTree(&CountryRootTree, "drzave.txt");
	
	return 0;
}


	

int ReadFromCountryFile(countryPosition countriesListHead, char* countriesFile)
{
	FILE* file = NULL;
	file = fopen(countriesFile,"r");
	if (!file) {
		printf("File not opened!");
		return -1;
	}

	char country[50];
	char CountryTownFile[50];

	while (fscanf(file, " %s %s%*c", country, CountryTownFile)==2) {
		
		AddCountryToList(countriesListHead, country, CountryTownFile);
	}

	//CalculateHashIndex(country,)


	
	return 0;
}

int AddCountryToList(countryPosition countriesListHead, char* country, char* TownFile)
{
	countryPosition NewCountry = (countryPosition)malloc(sizeof(Country));
	if (!NewCountry) {
		printf("error allocating memory!");
		return -1;
	}
	strcpy(NewCountry->countryName, country);
	NewCountry->next=NULL;
	NewCountry->townRootTree=NULL;

	countryPosition temp = countriesListHead;

	while (temp->next != NULL) {

		if (strcmp(country, temp->next->countryName) < 0) {
			break;
		}

		temp = temp->next;
	}

	NewCountry->next = temp->next;
	temp->next = NewCountry;

	townPosition TownTreeRoot = (townPosition)malloc(sizeof(Town));
	if (!TownTreeRoot) {
		printf("error allocating memory!");
		return -1;
	}
	
	TownTreeRoot->left = NULL;
	TownTreeRoot->right = NULL;
	NewCountry->townRootTree = NULL;
	NewCountry->townRootTree=ReadTownFileAndAddToTree(NewCountry->townRootTree, TownFile);

	return 0;
}

townPosition ReadTownFileAndAddToTree(townPosition townRoot, char* TownFile)
{
	FILE* file = NULL;
	file = fopen(TownFile, "r");
	if (!file) {
		printf("File not opened!");
		return -1;
	}
	townPosition NewTown = NULL;
	char town[50]="";
	int population=0;

		/*fscanf(file, " %s, %d.\n", town, &population);
		strcpy(townRoot->townName, town);
		townRoot->population = population;*/
		while (fscanf(file, " %s %d\n", town, &population) == 2) {
			
			NewTown = createNewTown(town, population);
			
			townRoot=AddTownToTree(townRoot, NewTown);
		
	}

	fclose(file);
	return townRoot;
}

townPosition AddTownToTree(townPosition townRoot, townPosition NewTown)
{
	if (townRoot == NULL) {
		return NewTown;
	}
	
	else {
		
		int populationComparison = townRoot->population - NewTown->population;
		if (populationComparison > 0) {
			townRoot->right = AddTownToTree(townRoot->right, NewTown);
		}
		else if (populationComparison < 0) {
			townRoot->left = AddTownToTree(townRoot->left, NewTown);
		}
		else {
			int nameComparison = strcmp(NewTown->townName, townRoot->townName);
			if (nameComparison < 0) {
				townRoot->left = AddTownToTree(townRoot->left, NewTown);
			}
			else {
				townRoot->right = AddTownToTree(townRoot->right, NewTown);
			}
		}
	}
	return townRoot;
}

int PrintCountryList(countryPosition countryHeadList) {
	countryPosition currentCountry = countryHeadList->next;
//townPosition currentTreeNode = currentCountry->townRootTree;
	while (currentCountry!=NULL) {
		printf("\n%s", currentCountry->countryName);
		printTownTree(currentCountry->townRootTree);
		currentCountry = currentCountry->next;
	}
	return 1;
}

int printTownTree(townPosition townRootTree) {
	if (townRootTree != NULL) {
		if (townRootTree->left != NULL) {
			printTownTree(townRootTree->left);
		}

		// Print the town information
		printf("\n\t%s %d", townRootTree->townName, townRootTree->population);

		if (townRootTree->right != NULL) {
			printTownTree(townRootTree->right);
		}
	}

	return EXIT_SUCCESS;
}

townPosition createNewTown(char* townName, int townPopulation) {
	townPosition town = NULL;
	town = (townPosition)malloc(sizeof(Town));
	if (!town) {
		printf("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(town->townName, townName);
	town->population = townPopulation;
	town->next = NULL;
	town->left = NULL;
	town->right = NULL;

	return town;
}



countryPosition AddCountryToTree(countryPosition CountryTreeRoot, countryPosition NewCountry, char* CountryTownFile)
{
	if (CountryTreeRoot == NULL) {
		return NewCountry;
	}
	else
	{
		if (strcmp(NewCountry->countryName, CountryTreeRoot->countryName) < 0) {
			CountryTreeRoot->left = AddCountryToTree(CountryTreeRoot->left, NewCountry, CountryTownFile);
		}
		else {
			CountryTreeRoot->right = AddCountryToTree(CountryTreeRoot->right, NewCountry, CountryTownFile);
		}
	}

	

	
	
	return CountryTreeRoot;
}

countryPosition CreateNewCountry(char* country) {
	countryPosition NewCountry = (countryPosition)malloc(sizeof(Country));
	if (!NewCountry) {
		printf("error allocating memory!");
		return NULL;
	}
	strcpy(NewCountry->countryName, country);
	NewCountry->left = NULL;
	NewCountry->right = NULL;
	return NewCountry;
}


int printCountryTree(countryPosition countryRootTree) {
	if (countryRootTree != NULL) {
		if (countryRootTree->left != NULL) {
			printCountryTree(countryRootTree->left, countryRootTree);
		}
		countryRootTree->townListHead;
		// Print the town information
		printf("\n%s", countryRootTree->countryName);
		//printTownList(townHead);
		printTownList(countryRootTree->townListHead);
		if (countryRootTree->right != NULL) {
			printCountryTree(countryRootTree->right, countryRootTree);
		}
		printf("\n");
	}

	return EXIT_SUCCESS;
}
int ReadFromCountryFileAddToTree(countryPosition CountryTreeRoot, char* countriesFile) {
	FILE* file = NULL;
	file = fopen(countriesFile, "r");
	if (!file) {
		printf("File not opened!");
		return -1;
	}
	char country[50];
	char CountryTownFile[50];
	countryPosition NewCountry = NULL;
	
	



	if (fscanf(file, " %s %s%*c", country, CountryTownFile) == 2) {
		NewCountry = CreateNewCountry(country);
		CountryTreeRoot = NewCountry;
		

		ReadTownFileAndAddToList( CountryTownFile, CountryTreeRoot);
		
	}
	while (fscanf(file, " %s %s%*c", country, CountryTownFile) == 2) {
		NewCountry = CreateNewCountry(country);
		CountryTreeRoot = AddCountryToTree(CountryTreeRoot, NewCountry, CountryTownFile);
		ReadTownFileAndAddToList(CountryTownFile, CountryTreeRoot);
		
	}
	


	return 0;
}

int ReadTownFileAndAddToList(char* TownFile,countryPosition CountryTreeRoot)
{	
	FILE* file = NULL;
	file = fopen(TownFile, "r");
	if (!file) {
		printf("File not opened!");
		return -1;
	}
	townPosition TownHead = (townPosition)malloc(sizeof(Town));
	if (!TownHead) {
		printf("error allocating memory!");
		return NULL;
	}
	TownHead->next = NULL;
	TownHead->left = NULL;
	TownHead->right = NULL;

	townPosition NewTown = NULL;
	char TownName[50];
	int population;
	while (fscanf(file, "%s %d%*c", TownName, &population)==2) {
		NewTown = createNewTown(TownName, population);
		AddTownTolist(TownHead, NewTown);
		
	}

	

	fclose(file);
	return 1;
}

int AddTownTolist(townPosition townHead, townPosition NewTown)
{	
	townPosition temp = townHead;

	while (temp->next != NULL) {
		if (NewTown->population > temp->next->population) {
			break;
		}
		else if (NewTown->population == temp->next->population) {
			if (temp->next->townName != NULL && strcmp(NewTown->townName, temp->next->townName) < 0) {
				break;
			}
		}
		temp = temp->next;
	}

	NewTown->next = temp->next;
	temp->next = NewTown;
	return 0;
}

int printTownList(townPosition townHead)
{
	if (townHead == NULL) {
		return 0;
	}
	townPosition currentTown = townHead->next;
	//townPosition currentTreeNode = currentCountry->townRootTree;
	while (currentTown != NULL) {
		printf("%s\t", currentTown->townName);
		
		currentTown = currentTown->next;
	}
	return 1;
}


