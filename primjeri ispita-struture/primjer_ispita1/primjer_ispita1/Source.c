
// radi za duju
/* Napisati program koji iz datoteke èita imena studenata.Nakon što se proèita
ime jednog studenta dodijeli mu se ocjena iz predmeta
(slucajna vrijednost od 1 do 5) i sprema se u listu sortirano
prema ocjenama od najveæe prema najmanjoj.Ispisati listu.
Slucajno generirati jednu ocjenu i izbrisati sve studente koji imaju tu ocjenu.Ispisati listu.
Za 3: Izmijeniti gornji zadatak na nacin da se studenti se sortiraju samo po ocjenama, nego i  po prezimenu i imenu. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX_FILENAME 256
#define MAX 5
#define MIN 1

struct studenti;
typedef struct studenti* position;
typedef struct studenti {
	char ime[MAX_FILENAME];
	char prezime[MAX_FILENAME];
	int ocjena;
	position next;
}Student;

int loadFile(char*, position);
int insertInList(position, position);
position makeNode(char*, char*, int);
int printList(position);
int deleteEl(position,int);
int deleteList(position);
int main()
{
	Student head = {
		.ime = {0},
		.prezime = {0},
		.ocjena = 0,
		.next = NULL
	};
	char filename[MAX_FILENAME] = { 0 };
	printf("unesite ime dat iz koje zelite citat\n");
	scanf("%s", filename);
	loadFile(filename, &head);

	int sluc_ocj = 0;
	srand(time(0));
	sluc_ocj = (rand() % (MAX - MIN + 1)) + MIN;
	printf("obrisat ce se studenti s ocjenom: %d \n", sluc_ocj);
	deleteEl(&head, sluc_ocj);
	printList(&head);

	deleteList(&head);


	return EXIT_SUCCESS;
}
int loadFile(char* filename, position head)
{
	srand(time(0));
	char ime[MAX_FILENAME] = { 0 };
	char prezime[MAX_FILENAME] = { 0 };
	int ocjena = 0;
	int brojac = 1;

	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju dat!");
		return ERROR;
	}
	
	while (!feof(fp))
	{
		if (fgetc(fp) == '\n')
			brojac++;
	}
	rewind(fp);
	for (int i = 0; i < brojac; i++) {
		fscanf(fp, "%s", ime);
		fscanf(fp, "%s", prezime);
		ocjena = (rand() % (MAX - MIN + 1)) + MIN;

		position novi = makeNode(ime, prezime, ocjena);
		insertInList(head, novi);
	}
	
	printList(head);
	fclose(fp);
	return EXIT_SUCCESS;
}
position makeNode(char* ime, char* prezime, int ocjena)
{
	position new_el = NULL;
	new_el = (position)malloc(sizeof(Student));
	if (new_el == NULL)
	{
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new_el->ime,ime);
	strcpy(new_el->prezime,prezime);
	new_el->ocjena = ocjena;
	return new_el;
}
int insertInList(position head, position new)
{	
		position p=NULL,prev=NULL;
		prev = head;
		p = head->next;
		while (p!= NULL && p->ocjena > new->ocjena) {
			prev = p;
			p = p->next;
		}
		new->next = prev->next;
		prev->next = new;

		return EXIT_SUCCESS;
}
int printList(position head)
{
	position p = head->next;
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int deleteEl(position p, int ocj)
{
	
	position temp = NULL;
	
	
	while (p->next != NULL)
	{
		if (p->next->ocjena == ocj)
		{
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		else
			p = p->next;
	}
	return EXIT_SUCCESS;
}

int deleteList(position head)
{
	position temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}
