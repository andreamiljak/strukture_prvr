
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX 50
#define EXIT_SUCCESS 0
#define ERROR -1



struct stablo_gradova;
typedef struct stablo_gradova* gradP;
typedef struct stablo_gradova {
	char ime_grada[MAX];
	int broj_stanovnika;
	gradP left;
	gradP right;
}StabloGradova;

struct lista_drzava;
typedef struct lista_drzava* pozicija;
typedef struct lista_drzava {
	char ime_drzave[MAX];
	char ime_dat[MAX];
	pozicija next;
	gradP cityRoot;
}ListaDrzava;

int citajDrzave(char*, pozicija);
pozicija napraviCvor_lista_drzava(char*, char*);
pozicija alokacija_drzave(pozicija);
int soriraniUnos_drzave(pozicija, pozicija);
int unesiNakon_lista_drzava(pozicija, pozicija);
int ispis_drzava(pozicija);

gradP citajGradove(char*);
gradP napraviCvor_stablo_gradova(char*, int);
gradP alokacija_gradovi(gradP);
gradP sortiraniUnos_gradovi(gradP, gradP);
int citycmp(gradP, gradP);
int ispis_gradova(gradP);

int main()
{
	ListaDrzava head;
	head.next = NULL;

	char filename[MAX] = { 0 };
	printf("unesite ime datoteke iz koje zelite procitati drzave\n");
	scanf("%s", filename);
	citajDrzave(filename, &head);
	ispis_drzava(&head);

	return 0;
}

int citajDrzave(char* ime, pozicija head)
{
	char imeDrzave[MAX] = { 0 };
	char imeDat[MAX] = { 0 };

	FILE* fp = NULL;
	fp = fopen(ime, "r");
	if (fp == NULL)
	{
		printf("greska pr otvaranju datoteke:(\n");
		return ERROR;
	}
	while (!feof(fp))
	{
		pozicija novi;
		fscanf(fp, "%s %s", imeDrzave, imeDat);
		novi = napraviCvor_lista_drzava(imeDrzave, imeDat);

		if (!novi)
			return ERROR;

		soriraniUnos_drzave(head, novi);
		novi->cityRoot = citajGradove(novi->ime_dat);
	}


	fclose(fp);
	return EXIT_SUCCESS;
}

pozicija napraviCvor_lista_drzava(char* imeDrzave, char* imeDat)
{
	pozicija cvor_liste = NULL;
	cvor_liste = alokacija_drzave(cvor_liste);

	strcpy(cvor_liste->ime_drzave, imeDrzave);
	strcpy(cvor_liste->ime_dat, imeDat);
	cvor_liste->next = NULL;
	cvor_liste->cityRoot = NULL;

	if (!cvor_liste)
		return NULL;

	return cvor_liste;
}

pozicija alokacija_drzave(pozicija p)
{

	p = (pozicija)malloc(sizeof(ListaDrzava));
	if (p == NULL)
	{
		printf("greska pri alokaciji memorije\n");
		return NULL;
	}
	return p;
}

int soriraniUnos_drzave(pozicija head, pozicija q)
{
	pozicija temp;
	for (temp = head; temp->next != NULL && strcmp(temp->next->ime_drzave, q->ime_drzave) < 0; temp = temp->next);
	unesiNakon_lista_drzava(temp, q);
	return EXIT_SUCCESS;
}

int unesiNakon_lista_drzava(pozicija p, pozicija novi)
{
	/*while (p->next != NULL)
		p = p->next;*/
	novi->next = p->next;
	p->next = novi;

	return EXIT_SUCCESS;
}

gradP citajGradove(char* imeDat)
{
	gradP root = NULL;
	char ime[MAX] = { 0 };
	int br_stan = 0;
	FILE* fp = NULL;
	fp = fopen(imeDat, "r");
	if (!fp)
	{
		printf("greska pri otvaranju datoteke\n");
		return NULL;
	}
	while (!feof(fp))
	{
		gradP grad = NULL;
		fscanf(fp, "%s %d", ime, &br_stan);
		grad = napraviCvor_stablo_gradova(ime, br_stan);

		if (!grad)
			return NULL;
		root = sortiraniUnos_gradovi(root, grad);
	}

	fclose(fp);
	return root;
}

gradP napraviCvor_stablo_gradova(char* imeGrada, int brojStanovnika)
{
	gradP cvor_stabla = NULL;
	cvor_stabla = alokacija_gradovi(cvor_stabla);
	strcpy(cvor_stabla->ime_grada, imeGrada);
	cvor_stabla->broj_stanovnika = brojStanovnika;
	cvor_stabla->left = NULL;
	cvor_stabla->right = NULL;

	if (!cvor_stabla)
		return NULL;
	return cvor_stabla;
}

gradP alokacija_gradovi(gradP p)
{
	p = (gradP)malloc(sizeof(StabloGradova));
	if (p == NULL)
	{
		printf("greska pri alokaciji memorije\n");
		return NULL;
	}
	return p;
}

gradP sortiraniUnos_gradovi(gradP curr, gradP novi_cvor)
{
	int rez = 0;

	if (curr == NULL)
		return novi_cvor;

	rez = citycmp(curr, novi_cvor);
	if (rez < 0)
	{
		curr->right = sortiraniUnos_gradovi(curr->right, novi_cvor);
	}
	else if (rez > 0)
	{
		curr->left = sortiraniUnos_gradovi(curr->left, novi_cvor);
	}
	else
		printf("taj grad vec postoji\n");
	return curr;

}

int citycmp(gradP g1, gradP g2)
{
	int rezultat = 0;
	rezultat = g1->broj_stanovnika - g2->broj_stanovnika;
	if (rezultat == 0)
		rezultat = strcmp(g1->ime_grada, g2->ime_grada);

	return rezultat;
}

int ispis_drzava(pozicija p)
{
	pozicija q = NULL;
	q = p->next;
	while (q != NULL)
	{
		printf("%s\n", q->ime_drzave);
		ispis_gradova(q->cityRoot);
		q = q->next;
	}
}

int ispis_gradova(gradP root)
{
	if (!root)
	{
		return ERROR;
	}
	ispis_gradova(root->right);
	printf("\t%s %d\r\n", root->ime_grada, root->broj_stanovnika);
	ispis_gradova(root->left);

	return EXIT_SUCCESS;

}
