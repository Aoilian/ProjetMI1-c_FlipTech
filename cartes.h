#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLIP7 94
#define FOIS2 15
#define PLUS2 2
#define PLUS4 4
#define PLUS6 6
#define PLUS8 8
#define PLUS10 10
#define SPECIAL1 1  /* STOP */
#define SPECIAL2 2  /* TROIS A LA SUITE */
#define SPECIAL3 3  /* SECONDE CHANCE */

/* une carte du jeu */

typedef struct {
    char type; /* 'N' = carte numéro, 'B' = carte bonus, 'S' = carte spéciale */
    int numero;  /* de 12 à 0 */
    int bonus; /* 6 cartes bonus */
    int speciale; /* 9 cartes spéciales */
} Carte;

/* le paquet de cartes */

typedef struct {
    Carte cartes[FLIP7];
    int nbCartes; /* nombre de cartes restantes dans la pile */
} Paquet;

/* les statistiques */

typedef struct {
    int nbNumero; /* nombre de cartes numéro piochées */
    int nbBonus; /* nombre de cartes bonus piochées */
    int nbSpeciale; /* nombre de cartes spéciale piochées */
} Stats;

void afficherPaquet(Paquet *p);
void creerPaquet(Paquet *p);
void melanger(Paquet *p);
Carte piocher(Paquet *p);
void majStats(Paquet *p, Stats *s);
void afficherCarte(Carte c);