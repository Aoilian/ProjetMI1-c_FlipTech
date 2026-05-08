#ifndef MANCHE_H //Garde d'inclusion pour éviter les inclusions multiples
#define MANCHE_H 

#include <stdbool.h>
#include "structure.h"


void decision(int* piocher,Perso* joueur);
void nmbJoueurs(int* nbJoueurs);
bool Flip7(Perso joueur);
bool NoDoublon(Carte carte, Perso joueur);
void preparerNouvelleManche(Perso* Joueurs, int nbJoueurs,Paquet* p, int compteur);
bool MancheTerminee(Perso* joueurs, int nbjoueur);
void lancerManche(Perso* Joueurs, int nbJoueurs, Paquet *paquet, int* nbpioche, bool* doublon);
void enregistrerJoueurs(Perso* joueurs, int n);

#endif //Fin de la garde d'inclusion
