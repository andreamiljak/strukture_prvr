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
void UnosK(ljud head, ljud p);
ljud Pronadi(ljud, char*);
void izbrisi(int, ljud);



int main(void)
{
	Osoba head;
	char temp[MAX] = { 0 };
	head.next = NULL;
	ljud p = NULL;
	ljud q = NULL;
	int odabir = 0;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;
	int i;

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
	scanf("%d", &i);
	izbrisi(i,&head);
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
	int i = 0;
	p = head->next;
	while (p != NULL) {
		q = p->next;
		printf("%d. %s\t %s\t %d\n", i+1, p->ime, p->prezime, p->godina);
		p = q;
		i++;
	}
}

void UnosK(ljud head, ljud p) {
	while (head->next != NULL)
		head = head->next;
	p->next = head->next;
	head->next = p;
}

ljud Pronadi(ljud head, char* temp)
{
	ljud q = NULL;
	q = head->next;
	while (q != NULL) {
		if (strcmp(q->prezime, temp) == 0)
			return q;
		q= q->next;
	}
	printf("neuspjesno pretrazivanje :(\n");
	return NULL;
}
void izbrisi(int n, ljud head) {
	ljud temp1 = head;
	int i;
	for (i = 0; i < n - 1; i++) {
		temp1 = temp1->next;
	}
	ljud temp2 = temp1->next;
	temp1->next = temp2->next;
	free(temp2);
}
