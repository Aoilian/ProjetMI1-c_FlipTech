#ifndef SCORE_H //Garde d'inclusion pour éviter les inclusions multiples
#define SCORE_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char type; // 'N' = carte numéro, 'B' = carte bonus, 'S' = carte spéciale
    int numero;  // de 12 à 0 
    int bonus; // 6 cartes bonus 
} Carte;

typedef struct{
	Carte carte[7];
	unsigned int score;
	unsigned int nbcarte;
	char prenom[255];
}Perso;

typedef struct {
    Carte cartes[85];
    int nbCartes; // nombre de cartes restantes dans la pile
} Paquet;

typedef struct {
    int nbNumero; // nombre de cartes numéro piochées
    int nbBonus; // nombre de cartes bonus piochées
    int nbSpeciale; // nombre de cartes spéciale piochées
} Stats;

void Maj(char* prenom);
void Min(char* prenom);
bool PrenomValide(char* prenom);
int PersoValide(Perso a);
unsigned int AjouterBonus(Perso a, int bonus);
bool FinDePartie(Perso* joueurs, Paquet pioche, int nbjoueur);
void reinitialiserJoueur(Perso* joueurs, int nbjoueur);
Perso* designerGagnant(Perso* joueurs, int taille);
void Enregistrejoueurs(Perso* a, int nbjoueur);

#endif //Fin de la garde d'inclusion
