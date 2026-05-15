#ifndef SCORE_H //Garde d'inclusion pour éviter les inclusions multiples
#define SCORE_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structure.h"

bool PrenomValide(char* prenom);
int PersoValide(Perso a);
unsigned int AjouterBonus(unsigned int score, int bonus);
void CalculScore(Perso* joueurs, Carte* main, int taille,bool doublon);
bool FinDePartie(Perso* joueurs, Paquet pioche, int nbjoueur);
void reinitialiserJoueur(Perso* joueurs, int nbjoueur);
Perso* designerGagnant(Perso* joueurs, int taille);
void Enregistrejoueurs(Perso* a, int nbjoueur);

#endif //Fin de la garde d'inclusion
