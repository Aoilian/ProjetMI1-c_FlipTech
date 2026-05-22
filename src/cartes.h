#ifndef CARTES_H // Garde d'inclusion pour éviter les inclusions multiples
#define CARTES_H

#include "structure.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define FLIP7 86
#define PLUS2 1
#define PLUS4 2
#define PLUS6 3
#define PLUS8 4
#define PLUS10 5
#define FOIS2 6
#define STOP 7

void RemplirPaquetNumero(Paquet *p, int *position, int numero);
void creerPaquet(Paquet *p, int nbJoueurs);
void melanger(Paquet *p);
Carte piocher(Paquet *p);
void carteStop(Perso *joueur, Perso *joueurs, int nbjoueur, Carte c);

#endif // Fin de la garde d'inclusion