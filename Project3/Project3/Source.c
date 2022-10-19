#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_BROJ_BODOVA (50)

typedef struct {
	char ime[50];
	char prezime[50];
	int bodovi;


} studenti;

int countStudents(char* filename);
int loadFile(char* filename, studenti *student);
void ispis(studenti *student, int brojStudenata);

int main(void)
{
	char filename[MAX_FILE_NAME] = { 0 };
	printf("Insert filename ");
	scanf(" %s", filename);
	int brojStudenata = countStudents(filename);

	printf("Broj studenata u datoteci %s je %d", filename, countStudents(filename));


/*alokacija*/

	studenti* student;
	student = (studenti*)malloc(brojStudenata * sizeof(studenti));
	loadFile(filename, student);
	ispis(student, brojStudenata);
	return 0;
}


int countStudents(char* filename)
{
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File %s didn't open\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
		}
		while (!feof(fp)) {
				fgets(buffer, MAX_LINE, fp); 
			if (strcmp("\n", buffer) != 0) {
				count++;
			}
		



		}

		fclose(fp);
		return count;

}

int loadFile(char* filename, studenti *student) {
	FILE* fp = NULL;
	int i = 0;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", student[i].ime);
		fscanf(fp, "%s", student[i].prezime);
		fscanf(fp, "%d", &student[i].bodovi);
		i++;
	}

	fclose(fp);
	return 0;
}

void ispis(studenti* student, int numStudents) {
	float relativePointsNum;
	for (int i = 0; i < numStudents; i++) {
		printf("%d. student: ", i + 1);
		relativePointsNum = ((float)student[i].bodovi / MAX_BROJ_BODOVA) * 100;
		printf(" Ime: %s\n Prezime: %s\n Apsolutni broj bodova: %d\n Relativni broj bodova: %f\n", student[i].ime, student[i].prezime, student[i].bodovi, relativePointsNum);
	}
}
