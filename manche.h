#ifndef MANCHE_H //Garde d'inclusion pour éviter les inclusions multiples
#define MANCHE_H 

include <stdbool.h>
#define TAILLE 255
#define MAIN 7

void decision(int* piocher,Perso* joueur);
void nmbJoueurs(int* nbJoueurs);
bool Flip7(Perso joueur);
bool NoDoublon(Carte carte, Perso joueur);
void preparerNouvelleManche(Perso* Joueurs, int nbJoueurs,Paquet* p)
bool MancheTerminee(Perso* joueurs, int nbjoueur)
void lancerManche(Perso* Joueurs, int nbJoueurs);
void enregistrerJoueurs(Perso* joueurs, int n);

#endif //Fin de la garde d'inclusion
