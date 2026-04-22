#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
	unsigned int carte[7];
	unsigned int score;
	unsigned int nbcarte;
	char prenom[255];
}Perso;

int PersoValide(Perso a);
bool FinDePartie(Perso* joueurs, unsigned int* pioche, int taille);
void reinitialiserJoueur(Perso* joueurs, int nbjoueur);
unsigned int calculScoreMancheTot(Perso a, int bonus);
Perso* designerGagnant(Perso* joueurs, int taille)
void Enregistrejoueurs(Perso* a, int nbjoueur);
