#ifndef CARTES_H //Garde d'inclusion pour éviter les inclusions multiples
#define CARTES_H 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

#define FLIP7 85
#define FOIS2 1
#define PLUS2 2
#define PLUS4 3
#define PLUS6 4
#define PLUS8 5
#define PLUS10 6

void creerPaquet(Paquet *p);
void melanger(Paquet *p);
Carte piocher(Paquet *p);
void majStats(Carte n, Stats *s);
void afficherCarte(Carte c);

#endif //Fin de la garde d'inclusion