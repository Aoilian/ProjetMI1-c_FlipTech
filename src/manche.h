#ifndef MANCHE_H // Garde d'inclusion pour éviter les inclusions multiples
#define MANCHE_H

#include "structure.h"
#include <stdbool.h>

bool PrenomValide(char *prenom);
int PersoValide(Perso a);
bool PrenomDejaUtilise(Perso *joueurs, char *prenom, int nbjoueurActuel);
void Decision(int *piocher, Perso *joueur);
void AfficherRegle();
void VoirRegle();
void nmbJoueurs(int *nbJoueurs);
bool Flip7(Perso joueur);
bool Doublon(Perso *joueur);
void preparerNouvelleManche(Perso *Joueurs, int nbJoueurs, Paquet *p,
                            int compteur);
bool MancheTerminee(Perso *joueurs, int nbjoueur);
void lancerManche(Perso *Joueurs, int nbJoueurs, Paquet *paquet);
void InitialiseJoueurs(Perso *joueurs, int n);

#endif // Fin de la garde d'inclusion
