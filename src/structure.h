#ifndef STRUCTURE_H // Garde d'inclusion pour éviter les inclusions multiples
#define STRUCTURE_H

#include <stdbool.h>
#define TAILLE_PRENOM 80
#define MAIN 14 // Taille maximale de la main d'un joueur : 6 cartes bonus + 7 cartes numero + 1 carte stop

typedef struct {
  char type;    // 'N' = carte numéro, 'B' = carte bonus, 'S' = carte spéciale
  int numero;   // Valeur de la carte numéro de 0 à 12, est à 0 pour les autres types
  int bonus;    // Valeur de la carte bonus, est à 0 pour les autres types
  int speciale; // Valeur de la carte spéciale, est à 0 pour les autres types
} Carte;

typedef struct {
  Carte carte[MAIN]; // Main actuelle du joueur
  unsigned int score; // Cumul des points sur toutes les manches jouées
  unsigned int nbcarte; // Nombre de carte actuellement dans sa main
  char prenom[TAILLE_PRENOM]; // Prenom du joueur
  bool Ajouer; // Vaut false si le joueur est encore dans la manche et true sinon
  bool doublon; // Vaut true si le joueur  a pioché une carte numéro qu'il possédait déjà dans sa main
} Perso;

typedef struct {
  Carte *cartes; // Alloué dynamiquement, contient toutes les cartes dans le paquet
  int nbCartes; // Nombre de cartes encore disponible dans le paquet
} Paquet;

#endif // Fin de la garde d'inclusion
