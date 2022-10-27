#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR (-1)
#define MAX_NAME (120)
typedef struct osoba* p_osoba;
typedef struct osoba {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int godiste;
	p_osoba sljedeca_osoba;
};
int UnosP(char*, char*, int, p_osoba);
int UnosK(char*, char*, int, p_osoba);
p_osoba Trazi(char*, p_osoba);
p_osoba TraziPret(char*, p_osoba); //ova funkcija nam pomaze kod brisanja elemenata
int Brisi(char*, p_osoba);
int Ispis(p_osoba);
int main()
{
	struct osoba head=NULL;
	head.sljedeca_osoba = NULL;
	p_osoba nadjena_osoba;
	char ulazno_ime[MAX_NAME] = { 0 };
	char ulazno_prezime[MAX_NAME] = { 0 };
	char trazeno_prezime[MAX_NAME] = { 0 };
	int ulazno_godiste = 0;
	int i = 0;
	char odabir = { 0 };;
	printf("Zelite li unjeti osobu na pocetak liste \nn(ne)\nd(da)\n");
	scanf("%c", &odabir);
	for (i = 0; odabir != 'n'; i++)
	{
		printf("IME: ");
		scanf(" %[^\n]", ulazno_ime);
		printf("PREZIME: ");
		scanf(" %[^\n]", ulazno_prezime);
		printf("GODISTE: ");
		scanf(" %d", &ulazno_godiste);
		UnosP(ulazno_ime, ulazno_prezime, ulazno_godiste, &head);
		printf("Zelite li unjeti jos jednu osobu na pocetak liste \nn(ne)\nd(da)\n");
		scanf(" %c", &odabir);
	}
	printf("Vasa unesena lista izgleda ovako:\n");
	Ispis(head.sljedeca_osoba);
	printf("\nako ste zaboravili dodati neku osobu, zelite li je dodati na kraj liste ?\nn(ne)\nd(da)\n");
	scanf(" %c", &odabir);
	for (i = 0; odabir != 'n'; i++)
	{
		printf("IME: ");
		scanf(" %[^\n]", ulazno_ime);
		printf("PREZIME: ");
		scanf(" %[^\n]", ulazno_prezime);
		printf("GODISTE: ");
		scanf(" %d", &ulazno_godiste);
		UnosK(ulazno_ime, ulazno_prezime, ulazno_godiste, &head);
		printf("Zelite li unjeti jos jednu osobu na kraj liste \nn(ne)\nd(da)\n");
		scanf(" %c", &odabir);
	}
	printf("Zelite li naci odredjenu osobu u listi?\nn(ne)\nd(da)\n");
	scanf(" %c", &odabir);
	switch (odabir)
	{
	case'n':
		printf("U redu.");
		break;
	case 'd':
		printf("Unesite prezime trazene osobe:\n");
		scanf(" %s", &trazeno_prezime);
		nadjena_osoba = Trazi(trazeno_prezime, head.sljedeca_osoba);

		printf("ostali podatci te osobe su:\nime: %s\nprezime: %s\nodiste: %d\n", nadjena_osoba->ime, nadjena_osoba->prezime, nadjena_osoba->godiste);
		break;
	}
	printf("Zelite li obristai odredjenu osobu iz liste?\nn(ne)\nd(da)\n");
	scanf(" %c", &odabir);
	switch (odabir)
	{
	case'n':
		printf("U redu.\n");
		break;
	case'd':
		printf("koga zelite izbristai?\nUnesite prezime te osobe\n");
		scanf("%s", trazeno_prezime);
		Brisi(trazeno_prezime, &head);
		break;
	}

	printf("\nKonacna unesena lista je sljedeca:\n");
	Ispis(head.sljedeca_osoba);
	return EXIT_SUCCESS;
}
int UnosP(char* ulazno_ime[MAX_NAME], char* ulazno_prezime[MAX_NAME], int ulazno_god, p_osoba p)
{
	p_osoba q = NULL;
	q = (p_osoba)malloc(sizeof(struct osoba));
	if (!q)
	{
		printf("Alokacija memorije neuspjesna.\n\r");
		return ERROR;
	}
	strcpy(q->ime, ulazno_ime);
	strcpy(q->prezime, ulazno_prezime);
	q->godiste = ulazno_god;
	q->sljedeca_osoba = p->sljedeca_osoba;
	p->sljedeca_osoba = q;
	return EXIT_SUCCESS;
}
int UnosK(char* ulazno_ime[MAX_NAME], char* ulazno_prezime[MAX_NAME], int ulazno_godiste, p_osoba p)
{
	p_osoba q;
	q = (p_osoba)malloc(sizeof(struct osoba));
	if (!q)
	{
		printf("Alokacija meorije neuspjesna");
		return ERROR;
	}
	while (p->sljedeca_osoba != NULL)
		p = p->sljedeca_osoba;

	strcpy(q->ime, ulazno_ime);
	strcpy(q->prezime, ulazno_prezime);
	q->godiste = ulazno_godiste;
	p->sljedeca_osoba = q;
	q->sljedeca_osoba = NULL;
	return EXIT_SUCCESS;
}
p_osoba Trazi(char* prezime_koje_se_trazi, p_osoba p)
{
	while (p != NULL && strcmp(p->prezime, prezime_koje_se_trazi))
		p = p->sljedeca_osoba;
	return p;
}
p_osoba TraziPret(char* prezime_koje_se_trazi, p_osoba p)
{
	p_osoba prev;
	prev = p;
	p = p->sljedeca_osoba;
	while (p != NULL && strcmp(p->prezime, prezime_koje_se_trazi))
	{
		prev = prev->sljedeca_osoba;
		p = p->sljedeca_osoba;
	}
	if (p == NULL)
		return NULL;
	else
		return prev;
}
int Brisi(char* prezime_koje_brisem, p_osoba p)
{
	p_osoba temp, prev;
	prev = TraziPret(prezime_koje_brisem, p);
	if (prev == NULL)
	{
		printf("Tog elementa nema.");
		return ERROR;
	}
	else
	{
		temp = prev->sljedeca_osoba;
		prev->sljedeca_osoba = temp->sljedeca_osoba;
		free(temp);
	}
	return EXIT_SUCCESS;
}
int Ispis(p_osoba p)
{
	while (p != NULL)
	{
		printf(" %s %s %d", p->ime, p->prezime, p->godiste);
		p = p->sljedeca_osoba;
		printf("\n");
	}
	return EXIT_SUCCESS;
}