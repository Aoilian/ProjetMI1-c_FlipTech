#ifndef SCORE_H // Garde d'inclusion pour éviter les inclusions multiples
#define SCORE_H

#include "structure.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool NomFichierValide(char *nom);
unsigned int AjouterBonus(unsigned int score, int bonus);
void CalculScore(Perso *joueurs, Carte *main, int taille, bool doublon);
bool FinDePartie(Perso *joueurs, Paquet pioche, int nbjoueur);
void GererEgalite (Perso *joueurs, int nbjoueur, Paquet *paquet, int *compteur);
void VideLaMain(Perso *joueurs, int nbjoueur);
Perso *designerGagnant(Perso *joueurs, int taille);
void Enregistrejoueurs(Perso *a, int nbjoueur);

#endif // Fin de la garde d'inclusion