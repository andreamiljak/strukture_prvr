/*napist program koji iz dat cita podatke o ljudima i kaficima u kojima su ljudi bili
napravit vezanu listu sortiranu po nazivima kafica,ispisat je te za trazei kafic napisat koliko ga je ljudi posjetilo i koji su to ljudi*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX_NAME 50
#define MAX_FILENAME 256

struct kafic;
typedef struct kafic* position;
typedef struct kafic {
	char ime_kafica[MAX_NAME];
	char ime_covjeka[MAX_NAME];
	char prezime_covjeka[MAX_NAME];
	position next;
}Kafic;

int citaj_dat(position,char*);
int sortirani_unos(position, position);
int print_list(position);
int posjetitelji(position, char*);
int brisi_listu(position);
int main()
{
	char filename[MAX_FILENAME] = { 0 };
	char kafic[MAX_NAME] = { 0 };
	Kafic head = {
		.ime_covjeka = {0},
		.prezime_covjeka={0},
		.ime_kafica = {0},
		.next = NULL
	};
	printf("unesite ime dat\n");
	scanf("%s", filename);
	printf("unesite ime trazenog kafica\n");
	scanf("%s", kafic);

	citaj_dat(&head, filename);
	print_list(&head);
	posjetitelji(&head,kafic);
	brisi_listu(&head);

	return 0;
}
int citaj_dat(position head, char* filename)
{
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 }, kafic[MAX_NAME] = { 0 };
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("greska pri otvaranju dat: ");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s", ime, prezime, kafic);
		position q = NULL;
		q = (position)malloc(sizeof(Kafic));
		if (q == NULL)
		{
			printf("greska  pri alokaciji mem\n");
			return ERROR;
		}
		strcpy(q->ime_covjeka, ime);
		strcpy(q->prezime_covjeka, prezime);
		strcpy(q->ime_kafica, kafic);

		sortirani_unos(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int sortirani_unos(position p, position q)
{
	while (p->next != NULL && strcmp(p->next->ime_kafica, q->ime_kafica) < 0)
		p = p->next;
	q->next = p->next;
	p->next = q;
	return EXIT_SUCCESS;
}

int print_list(position head)
{
	if (head == NULL)
	{
		printf("lista je praza");
		return ERROR;
	}
	position p = head->next;
	while (p!= NULL)
	{
		printf("%s %s %s\n", p->ime_covjeka, p->prezime_covjeka, p->ime_kafica);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int posjetitelji(position p, char* kafic) {
	int br = 0;
	printf("Ljudi koji su bili u trazenom kaficu:\n");
	while (p->next != NULL)
	{
		if (strcmp(p->next->ime_kafica,kafic)==0)
		{
			br++;
			printf("%s %s\n", p->next->ime_covjeka, p->next->prezime_covjeka);
		}
		p = p->next;
	}
	printf("Broj posjetitelja tog kafica: %d \n", br);
	return EXIT_SUCCESS;
}

int brisi_listu(position p)
{
	position temp = NULL;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}