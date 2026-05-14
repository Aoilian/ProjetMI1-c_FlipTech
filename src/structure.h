#ifndef STRUCTURE_H //Garde d'inclusion pour éviter les inclusions multiples
#define STRUCTURE_H 

#include <stdbool.h>
#define TAILLE 150
#define MAIN 14 // 6 cartes bonus + 7 cartes numero maximum + 1 carte stop

typedef struct {
    char type; // 'N' = carte numéro, 'B' = carte bonus
    int numero;  // de 12 à 0 
    int bonus; // 6 cartes bonus 
    int speciale; // 1 carte spéciale : la carte STOP
} Carte;

typedef struct{
	Carte carte[MAIN];
	unsigned int score;
	unsigned int nbcarte;
	char prenom[TAILLE];
	bool Ajouer;
    bool doublon;
}Perso;

typedef struct {
    Carte* cartes;
    int nbCartes; // nombre de cartes restantes dans la pile
} Paquet;

typedef struct {
    int nbNumero; // nombre de cartes numéro piochées
    int nbBonus; // nombre de cartes bonus piochées
    int nbSpeciale; // nombre de cartes spéciale piochées
} Stats;


#endif //Fin de la garde d'inclusion
