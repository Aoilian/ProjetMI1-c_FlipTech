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
// #define SPECIAL1 1  /* STOP */
// #define SPECIAL2 2  /* TROIS A LA SUITE */
// #define SPECIAL3 3  /* SECONDE CHANCE */

// void afficherPaquet(Paquet *p);
void creerPaquet(Paquet *p);
void melanger(Paquet *p);
Carte piocher(Paquet *p);
void majStats(Paquet *p, Stats *s);
void afficherCarte(Carte c);
