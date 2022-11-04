#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#define ERROR (-1)
#define MAX (50)
#define EXIT_SUCCESS (0)



struct osoba;
typedef struct osoba* ljud;
typedef struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int godina;
	ljud next;
} Osoba;

ljud Stvori(char*, char*, int);
int UnosP(ljud head, ljud p);
int Ispis(ljud head);
int UnosK(ljud head, ljud p);
ljud Pronadi(ljud, char*);
int Izbrisi(ljud, char*);
ljud PronadiPrethodni(ljud, char*);
int meni();
int unesipodatke(char*, char*, int*);
int UnesiPrije(ljud, char*);
int UnesiNakon(ljud, ljud, char*);
void unosDatoteka(char*, ljud);
void ispisDatoteke(char*, ljud);



int main(void)
{
	Osoba head = {
	.ime = {0},
	.prezime = {0},
	.godina = 0,
	.next = NULL
	};
	char temp[MAX] = { 0 };
	ljud p = NULL;
	ljud q = NULL;
	int odabir = 0;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;
	char filename[MAX] = { 0 };


	meni();

	return EXIT_SUCCESS;
}

ljud Stvori(char* ime, char* prezime, int godina) {
	ljud p = NULL;
	p = (ljud)malloc(sizeof(Osoba));
	if (!p)
	{
		printf("alokacija je neuspjesna :( \n");
		return NULL;
	}
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godina = godina;

	return p;
}

int UnosP(ljud head, ljud p)
{
	p->next = head->next;
	head->next = p;
	return EXIT_SUCCESS;
}

int Ispis(ljud head)
{
	ljud p = NULL;
	ljud q = NULL;
	int i = 0;
	p = head->next;
	while (p != NULL) {
		q = p->next;
		printf("%d. %s\t %s\t %d\n", i + 1, p->ime, p->prezime, p->godina);
		p = q;
		i++;
	}
	return EXIT_SUCCESS;
}

int UnosK(ljud head, ljud p) {
	while (head->next != NULL)
		head = head->next;
	p->next = head->next;
	head->next = p;
	return EXIT_SUCCESS;
}

ljud Pronadi(ljud head, char* temp)
{
	ljud q = NULL;
	q = head->next;
	while (q != NULL) {
		if (strcmp(q->prezime, temp) == 0)
			return q;
		q = q->next;
	}
	printf("neuspjesno pretrazivanje :(\n");
	return NULL;
}

ljud PronadiPrethodni(ljud p, char* prezime)
{
	ljud prev = NULL, curr = NULL;
	prev = p;
	curr = prev->next;
	while (curr != NULL && strcmp(curr->prezime, prezime) != 0)
	{
		prev = curr;
		curr = prev->next;

	}
	if (curr == NULL)
		return NULL;
	return prev;

}
int Izbrisi(ljud p, char* prezime)
{
	ljud prev = NULL;
	ljud curr = NULL;
	prev = PronadiPrethodni(p, prezime);
	if (prev == NULL)
		return ERROR;
	curr = prev->next;
	prev->next = prev->next->next;
	free(curr);
	return EXIT_SUCCESS;
}

int meni()
{
	Osoba head;
	char temp[MAX] = { 0 };
	head.next = NULL;
	ljud p = NULL;
	ljud q = NULL;
	ljud novi = NULL;
	int odabir = 0;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;
	char pronadi_prezime[MAX] = { 0 };
	char filename[1023] = { 0 };

	printf("zelite li unjeti ime na pocetak liste?\nda-> 1\nne-> 2\n");
	scanf("%d", &odabir);
	while (odabir == 1)
	{
		printf("IME: ");
		scanf(" %s", ime);
		printf("\nPREZIME: ");
		scanf(" %s", prezime);
		printf("\nGODINA: ");
		scanf("%d", &godina);
		//unesipodatke(ime,prezime,&godina);
		p = Stvori(ime, prezime, godina);
		UnosP(&head, p);
		printf("zelite li unjeti ime na pocetak liste?\nda-> 1\nne->2\n");
		scanf("%d", &odabir);

	}

	printf("zelite li unjeti ime na kraj liste?\nda-> 1\nne->2\n");
	scanf("%d", &odabir);
	while (odabir == 1)
	{
		printf("IME: ");
		scanf(" %s", ime);
		printf("\nPREZIME: ");
		scanf(" %s", prezime);
		printf("\nGODINA: ");
		scanf("%d", &godina);
		//unesipodatke(ime, prezime, godina);
		p = Stvori(ime, prezime, godina);
		UnosK(&head, p);
		printf("zelite li unjeti ime na kraj liste?\nda-> 1\n ne->2\n");
		scanf("%d", &odabir);

	}

	Ispis(&head);

	printf("unesite prezime za pronalazak\t");
	scanf("%s", temp);
	q = Pronadi(&head, temp);
	printf("%s\t%s\t%d", q->ime, q->prezime, q->godina);

	printf("\nkoji element liste zelite izbrisati?\n");
	scanf("%s", temp);
	Izbrisi(&head, temp);
	Ispis(&head);

	printf("prije kojeg elementa zelite unjeti novi?\n");
	scanf("%s", pronadi_prezime);

	printf("IME: ");
	scanf(" %s", ime);
	printf("\nPREZIME: ");
	scanf(" %s", prezime);
	printf("\nGODINA: ");
	scanf("%d", &godina);
	novi = Stvori(ime, prezime, godina);
	UnesiPrije(&head, pronadi_prezime, novi);
	Ispis(&head);

	printf("nakon kojeg elementa zelite unjeti novi?\n");
	scanf("%s", pronadi_prezime);
	printf("UNESITE PODATKE ZA NOVI ELEMENT\n");
	printf("IME: ");
	scanf(" %s", ime);
	printf("\nPREZIME: ");
	scanf(" %s", prezime);
	printf("\nGODINA: ");
	scanf("%d", &godina);
	novi = Stvori(ime, prezime, godina);
	UnesiNakon(&head, novi, pronadi_prezime);
	Ispis(&head);
	printf("sortirani unos:\n");
	Sort(&head);
	Ispis(&head);

	printf("unesite ime datoteke u koju zelite upisati listu\n");
	scanf(" %s", filename);
	unosDatoteka(filename, &head);
	Ispis(&head);

	return EXIT_SUCCESS;


}
/*
int unesipodatke(char* ime, char* prezime, int* godina)
{

	printf("IME: ");
	scanf(" %s", ime);
	printf("\nPREZIME: ");
	scanf(" %s", prezime);
	printf("\nGODINA: ");
	scanf("%d", &godina);
	return EXIT_SUCCESS;
}*/

int UnesiPrije(ljud p, char* prezime, ljud novi)
{
	ljud prev = NULL;
	prev = PronadiPrethodni(p, prezime);
	novi->next = prev->next;
	prev->next = novi;
	return EXIT_SUCCESS;

}

int UnesiNakon(ljud p, ljud novi, char* prezime)
{
	ljud curr = NULL;
	curr = Pronadi(p, prezime);
	novi->next = curr->next;
	curr->next = novi;
	return EXIT_SUCCESS;

}
int Sort(ljud p)
{
	ljud j, prev_j, temp, end;

	end = NULL;
	while (p->next != end)
	{

		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;

			}

			prev_j = j;
			j = j->next;
		}
		end = j;

	}
}
void unosDatoteka(char* filename, ljud head) {
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR;
	}
	head = head->next;
	while (head != NULL) {

		fprintf(fp, "\n%s %s %d", head->ime, head->prezime, head->godina);
		head = head->next;
	}
	fclose(fp);

}