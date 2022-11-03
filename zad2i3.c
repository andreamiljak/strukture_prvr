#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#define ERROR (-1)
#define MAX (50)
#define EXIT_SUCCESS (0)


struct lista;
typedef struct lista* position;

typedef struct lista
{
	char ime[MAX];
	char prezime[MAX];
	int godina;

	position next;
}lista;
int printMenu();

int UmetniP(position);
int UmetniK(position);
position PronadiPosljednji(position);
int Ispis(position);
int UmetniNakon(position, char*);
position Pronadi(position, char*);
int UmetniPrije(position, char*);
int UnesiPodatke(position);
position PronadiPrethodni(position, char*);
int Izbrisi(position, char*);
position PronadiMjesto(int, position);
void Brisi(position, int);

int main()
{
	int odabir = 0;
	char choice = 0;
	char prez[MAX] = { 0 };
	position head = NULL;
	head = (position)malloc(sizeof(lista));
	head->next = NULL;
	int status = EXIT_SUCCESS;
	position q = NULL;
	q = (position)malloc(sizeof(lista));

	//
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;

	printf("zelite li pristupit izborniku?\nda -> 1\nne -> 2\n");
	scanf(" %d", &odabir);


	do{
		printMenu();

		choice = getchar();
		choice = toupper(choice);

		switch (choice) {
		case 'A': 
			UnesiPodatke(q);
			status = UmetniP(head);
			break;
		
		case 'B': 
			UnesiPodatke(q);
			status = UmetniK(head);
			break;
		
		case 'C': 
			status = Ispis(head);
		
		case 'D': 
			printf("koji element zelite pronaci? (prezime)\n");
			scanf("%s", prez);
			Pronadi(head, prez);
			scanf(" %c", &choice);
			choice = toupper(choice);
			break;
		
		case 'E': 
			printf("koji element zelite izbrisat? (prezime)\n");
			scanf("%s", prez);
			status = Izbrisi(head, prezime);
			scanf(" %c", &choice);
			choice = toupper(choice);
			break;
		
		case 'X':
			odabir = 2;
			break;
		default: 
			printf("nije ponudeno frende ;) \n");
			break;
		
		}
		if (status == EXIT_SUCCESS) continue;
		else
			break;
		printMenu();

		scanf("  %c", &choice);
		choice = toupper(choice);
	} while (odabir!=2);

	/*

	UmetniNakon(head->next, prezime);

	Ispis(head->next, prezime);
	//UmetniPrije(head, prezime);
	*/
	return EXIT_SUCCESS;

}

int UmetniP(position p)
{
	position q = NULL;
	q = (position)malloc(sizeof(lista));
	if (q == NULL)
		return ERROR;
	UnesiPodatke(q);
	q->next = p->next;
	p->next = q;
	q->prev = p;
	if (q->next != NULL)
	{
		q->next->prev = q;
	}
	
	return EXIT_SUCCESS;
}

int UmetniK(position p)
{
	position last = NULL;
	last = PronadiPosljednji(p);
	UmetniP(last);
	return EXIT_SUCCESS;
}

position PronadiPosljednji(position p)
{
	while (p->next != NULL)
		p = p->next;
	return p;

}

int Ispis(position p)
{
	if (p == NULL)
	{
		printf("nema elemenata, lista je prazna!\n");
		return ERROR;

	}
	else
	{
		while (p != NULL)
		{
			printf("ime: %s\n", p->ime);
			printf("prezime: %s\n", p->prezime);
			printf("godiste: %d\n", p->godina);
			p = p->next;

		}
	}
	return EXIT_SUCCESS;

}

int UmetniNakon(position p, char* prezime)
{
	position prev = NULL;
	prev = Pronadi(p, prezime);
	if (prev == NULL)
		return ERROR;
	UmetniP(prev);
	return EXIT_SUCCESS;
}

position Pronadi(position p, char* prezime)
{
	while (p != NULL && strcmp(p->prezime, prezime) != NULL)
		p = p->next;

	if (p == NULL)
		printf("Takav element ne postoji\n");
	return p;
}

int UnesiPodatke(position q)
{

	printf("unesite ime\n");
	scanf("%s", q->ime);
	printf("unesite prezime\n");
	scanf("%s", q->prezime);
	printf("unesite godiste\n");
	scanf("%d", &q->godina);

	return EXIT_SUCCESS;
}

int printMenu()
{
	printf("ODABERITE:\n");
	printf("A -> za unos na pocetak\n");
	printf("B -> za unos na kraj\n");
	printf("C -> za ispis liste\n");
	printf("D -> pronalazi element(po prezimenu)\n");
	printf("E -> brise odredeni element (po prezimenu)\n");
	printf("X -> ako ste gotovi\n");

	return EXIT_SUCCESS;
	
}

int Izbrisi(position p, char* prezime)
{
	position prev = NULL;
	position curr = NULL;
	prev = PronadiPrethodni(p, prezime);
	if (prev == NULL)
		return ERROR;
	curr = prev->next;
	prev->next = prev->next->next;
	free(curr);
	return EXIT_SUCCESS;

}

position PronadiPrethodni(position p, char* prezime)
{
	position prev = NULL, curr = NULL;
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

int UmetniPrije(position p, char* prezime) {
	position prevp = NULL;
	prevp = PronadiPrethodni(p, prezime);
	if (prevp == NULL)
		return ERROR;
	UmetniP(prevp);
	return EXIT_SUCCESS;

}
/*
position PronadiMjesto(int n, position p)
{
	while (p->next != NULL && n > p->next->godina)
	{
		p = p->next;

	}
	return p;
}

void Brisi(position p, int x)
{
	while (p != NULL && p->godina != x)
	{
		p = p->next;

	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}


*/
