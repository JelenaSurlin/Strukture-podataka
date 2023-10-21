/*Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX_BR_BODOVA 50
#include <stdlib.h>

typedef struct {      //struktura studenta
	char ime[50];
	char prezime[50];
	double bodovi;

}student;

int èitanjeRedovaDatoteke();
double relativniBodovi(double bodovi);
student* dinamièkaAlokacija(int);

int main() {
	student *studenti;
	int brojRedova = 0;
	brojRedova = èitanjeRedovaDatoteke();


	if (brojRedova > 0) {

		studenti = dinamièkaAlokacija(brojRedova);

		for (int i = 0; i < brojRedova; i++) {
			printf("%d. student: \n", i + 1);
			printf("Ime: %s, prezime %s \n", studenti[i].ime, studenti[i].prezime);
			printf("Apsolutni broj bodova %.2f, relativni broj bodova %.2f \n", studenti[i].bodovi, relativniBodovi(studenti[i].bodovi));
		}
		free(studenti);

	}


	return 0;
}

int èitanjeRedovaDatoteke() {

	char charBuffer[1024] = "";
	int brojRedova = 0;

	FILE* filePointer = NULL;

	filePointer = fopen("studenti.txt", "r");

	if (filePointer == NULL) {
		printf("Datoteka nije pronadena");
		return 1;
	}

	while (!feof(filePointer)) {
		fgets(charBuffer, 1024, filePointer);	//èita datoteku dok ne doðe do kraja reda
		brojRedova++;
	}
	fclose(filePointer);

	return brojRedova;
}

student* dinamièkaAlokacija(int brojRedova) {
	student* studenti = NULL;
	FILE* filePointer = NULL;
	int i = 0;

	filePointer = fopen("studenti.txt", "r");

	if (filePointer == NULL) {
		printf("Datoteka nije pronadena");
		return NULL;
	}

	studenti = malloc(brojRedova * sizeof(student));

	while (!feof(filePointer)) {
		fscanf(filePointer, "%s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
		i++;
	}
	fclose(filePointer);
	return studenti;
}

double relativniBodovi(double bodovi) {
	return (bodovi / MAX_BR_BODOVA) * 100;
}
