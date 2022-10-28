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
void UnosP(ljud head, ljud p);
void Ispis(ljud head);
int UnosK(ljud head,ljud p);
ljud PronadiPosljednji(ljud head);

ljud Trazi(char*,ljud);


int main(void)
{
	Osoba head;
	head.next = NULL;
	ljud p = NULL;
	ljud q = NULL;
	int odabir = 0;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;
	char clan[MAX] = { 0 };

	printf("zelite li unjeti ime na pocetak liste?\nda-> 1\n ne->2\n");
	scanf("%d", &odabir);
	while (odabir == 1)
	{
		printf("IME: ");
		scanf(" %s", ime);
		printf("\nPREZIME: ");
		scanf(" %s", prezime);
		printf("\nGODINA: ");
		scanf("%d", &godina);
		p = Stvori(ime, prezime, godina);
		UnosP(&head, p);
		printf("zelite li unjeti ime na pocetak liste?\nda-> 1\n ne->2\n");
		scanf("%d", &odabir);

	}
	
	/*printf("zelite li unjeti ime na kraj liste?\nda-> 1\n ne->2\n");
	scanf("%d", &odabir);
	while (odabir == 1)
	{
		printf("IME: ");
		scanf(" %s", ime);
		printf("\nPREZIME: ");
		scanf(" %s", prezime);
		printf("\nGODINA: ");
		scanf("%d", &godina);
		q = Stvori(ime, prezime, godina);
		UnosK(&head, q);
		printf("zelite li unjeti ime na pocetak liste?\nda-> 1\n ne->2\n");
		scanf("%d", &odabir);

	}*/
	printf("kojeg clana liste zelite pronaci?\n");
	scanf(" %s", clan);
	q = Trazi(clan, head);
	printf("%s\t %s\t %d\n", q->ime, q->prezime, q->godina);
	Ispis(&head);

	

	return EXIT_SUCCESS;
}

ljud Stvori(char* ime, char* prezime, int godina) {
	ljud p = NULL;
	p = (ljud)malloc(sizeof(Osoba));
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godina = godina;
	if (!p)
	{
		printf("alokacija je neuspjesna :( \n");
		return NULL;
	}
	return p;
}

void UnosP(ljud head, ljud p)
{
	p->next = head->next;
	head->next = p;
}

void Ispis(ljud head)
{
	ljud p = NULL;
	ljud q = NULL;
	p = head->next;
	while (p != NULL) {
		q = p->next;
		printf("%s\t %s\t %d\n", p->ime, p->prezime, p->godina);
		p = q;
	}
}

ljud PronadiPosljednji(ljud p)
{
		while (p->next != NULL)
			p = p->next;
		return p;
}

int UnosK(ljud head,ljud p)
{

		ljud zadnji = NULL;
		zadnji = PronadiPosljednji(p);
		UnosP(head,zadnji);

		zadnji->next = p->next;
		p->next = zadnji;
		return 0;

}

ljud Trazi(char* clan, ljud p)
{
	while (p != 0 && p->prezime != clan)
	{
		p = p->next;
	}
	return p;
}