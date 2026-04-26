#ifndef MANCHE_H //Garde d'inclusion pour éviter les inclusions multiples
#define MANCHE_H 

#include <stdbool>
#define TAILLE 255
#define MAIN 7

void decision(int* piocher,Perso* joueur);
void nmbJoueurs(int* nbJoueurs);
bool tourTerminer(Perso* joueurs, int nbjoueur);
bool Flip7(Perso joueur);
bool NoDoublon(Carte carte, Perso joueur);
void lancerTour(Perso* Joueurs, int nbJoueurs);
void enregistrerJoueurs(Perso* joueurs, int n);

#endif //Fin de la garde d'inclusion
