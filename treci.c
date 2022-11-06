#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define ERROR (-1)
#define MAX (1024)
#define EXIT_SUCCESS (0)

struct osoba;
typedef struct osoba* ljud;
typedef struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int godina;
	ljud next;
} Osoba;

int printMenu();
ljud Stvori(char*, char*, int);
int UnosP(ljud head, ljud p);
int Ispis(ljud head);
int UnosK(ljud head, ljud p);
ljud Pronadi(ljud, char*);
int Izbrisi(ljud, char*);
ljud PronadiPrethodni(ljud, char*);
int unesipodatke();
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
	};
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina=0;
	ljud nova = NULL;
	nova = (ljud)malloc(sizeof(Osoba));
	ljud trazeni_el = NULL;
	trazeni_el = (ljud)malloc(sizeof(Osoba));
	ljud novi_el = NULL;
	novi_el = (ljud)malloc(sizeof(Osoba));
	
	int odabir=0;
	char temp[MAX] = { 0 };
	char pronadi_prezime[MAX] = { 0 };
	char filename[MAX] = { 0 };
	


	do {
		printMenu();
		scanf(" %d", &odabir);
		if (odabir == 1)
		{
			printf("IME: ");
			scanf(" %s", ime);
			printf("\nPREZIME: ");
			scanf(" %s", prezime);
			printf("\nGODINA: ");
			scanf("%d", &godina);
			nova = Stvori(ime, prezime, godina);
			UnosP(&head, nova);
		}
		else if (odabir == 2)
		{
			printf("IME: ");
			scanf(" %s", ime);
			printf("\nPREZIME: ");
			scanf(" %s", prezime);
			printf("\nGODINA: ");
			scanf("%d", &godina);
			nova = Stvori(ime, prezime, godina);
			UnosK(&head, nova);
		}
		else if (odabir == 3)
		{
			printf("koji element zelite izbrisati?\n(unessite prezime)\n");
			scanf("%s", temp);
			Izbrisi(&head, temp);
		}
		else if (odabir == 4)
		{
			printf("koji element zelite pronaci?\n(unessite prezime)\n");
			scanf(" %s", temp);
			trazeni_el = Pronadi(&head, temp);
			printf("%s\t%s\t%d", trazeni_el->ime, trazeni_el->prezime, trazeni_el->godina);
		}
		else if (odabir == 5)
		{
			printf("prije kojeg elementa zelite unjeti novi?\n");
			scanf("%s", pronadi_prezime);
			printf("Unesite podatke za novi element koji unosite\n");
			printf("IME: ");
			scanf(" %s", ime);
			printf("\nPREZIME: ");
			scanf(" %s", prezime);
			printf("\nGODINA: ");
			scanf("%d", &godina);
			novi_el = Stvori(ime, prezime, godina);
			UnesiPrije(&head, pronadi_prezime, novi_el);
		}
		else if (odabir == 6)
		{
			printf("nakon kojeg elementa zelite unjeti novi?\n");
			scanf("%s", pronadi_prezime);
			printf("Unesite podatke za novi element koji unosite\n");
			printf("IME: ");
			scanf(" %s", ime);
			printf("\nPREZIME: ");
			scanf(" %s", prezime);
			printf("\nGODINA: ");
			scanf("%d", &godina);
			novi_el = Stvori(ime, prezime, godina);
			UnesiNakon(&head, novi_el, pronadi_prezime);
		}
		else if (odabir == 7)
		{
			printf("sortirana lista:\n");
			Sort(&head);
			Ispis(&head);
		}
		else if (odabir == 9)
		{
			printf("unesite ime datoteke u koju zelite upisati listu\n");
			scanf(" %s", filename);
			unosDatoteka(filename, &head);
		}
		else if (odabir == 8)
		{
			Ispis(&head);
		}
	} while (odabir != 100);


	return EXIT_SUCCESS;
}
int printMenu()
{
	printf("\n\t\tMENI\n Odaberite:\n");
	printf("\t1  Za unos na pocetak liste\n");
	printf("\t2  Za unos na kraj liste\n");
	printf("\t3  Za brisanje elementa liste\n");
	printf("\t4  Za pronalaženje elementa liste\n");
	printf("\t5  Za unos prije odeðenog elementa liste\n");
	printf("\t6  Za unos nakon odeðenog elementa liste\n");
	printf("\t7  Za sortiranje liste\n");
	printf("\t8  Za ispis liste\n");
	printf("\t9  Za upis liste u datoteku\n");
	printf("\t100  Ako ste gotovi\n");

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

int UnosK(ljud head, ljud p) {
	while (head->next != NULL)
		head = head->next;
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

int unesipodatke()
{
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;
	
	return EXIT_SUCCESS;
}

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