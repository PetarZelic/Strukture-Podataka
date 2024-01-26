#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_POINTS 100

typedef struct _student {
	
	char ime[50];
	char prezime[50];
	double bodovi;

}studenti;

int izbrojRedove();


int main() {
	int brojRedova = 0;
	int i = 0;
	int j = 0;

	FILE* fp;
	studenti *student;

	brojRedova = izbrojRedove();
	printf("%d\n",brojRedova);

	fp = fopen("Text1.txt", "r");
	student = (studenti*)malloc(brojRedova * sizeof(studenti));
	
		
		while (fscanf(fp, "%s %s %lf", student[i].ime, student[i].prezime, &student[i].bodovi) == 3) {
			double relativniBodovi = calculateRelativePoints(student[i].bodovi);
			
			printf("%s %s %lf %lf\n", student[i].ime, student[i].prezime, student[i].bodovi, relativniBodovi);

			i++;
		}
		
	

	fclose(fp);

	return 0;
}

int izbrojRedove() {
	FILE* fp;
	int counter = 0;
	char buffer[128];
	char emptyLine[50] = { '\n' };
	fp = fopen("Text1.txt", "r");
	if (!fp) {
		printf("neuspjelo otvaranje datoteke");
		return -1;
	}

	while (!feof(fp)) {
		fgets(buffer, 128, fp);
		if(strcmp(buffer,emptyLine)!=0)
		
		counter++;
	}
	fclose(fp);
	return counter;
}
calculateRelativePoints(double bodovi){
	return ((bodovi / MAX_POINTS) * 100);
}


