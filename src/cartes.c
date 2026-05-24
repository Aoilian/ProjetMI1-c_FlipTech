#include "cartes.h"
#include "affichage.h"
#include "erreur.h"
#include "manche.h"
#include "structure.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remplis le paquet avec les cartes numéro 
void RemplirPaquetNumero(Paquet *p, int *position, int numero) {
  if (p == NULL || position == NULL || (numero < 1 || numero > 12)) {
    printf("\nErreur de programation !\n");
    exit(ERREUR_7);
  }
  for (int i = 0; i < numero; i++) {
    p->cartes[*position].type = 'N';
    p->cartes[*position].numero = numero;
    p->cartes[*position].bonus = 0;
    p->cartes[*position].speciale = 0;
    (*position)++;
  }
}

// Initialise le paquet avec toutes les cartes du jeu
void creerPaquet(Paquet *p, int nbJoueurs) {
  if (p == NULL || nbJoueurs < 3) {
    printf("\nErreur de programmation !\n");
    exit(ERREUR_8);
  }

  int pos = 0;
  // 1 paquet pour 3 à 10 joueurs, 2 paquet pour 11 à 19 joueurs, etc.
  int nbPaquet = (nbJoueurs + 9) / 10;

  p->cartes = malloc(sizeof(Carte) * (nbPaquet * FLIP7));

  if (p->cartes == NULL) {
    printf("Allocation échouée !");
    exit(ERREUR_9);
  }

  // On créer plusieurs paquet selon le nombre de joueurs
  for (int i = 0; i < nbPaquet; i++) {
    // Initialisation des 79 cartes numéro
    for (int j = 1; j <= 12; j++) {
      RemplirPaquetNumero(p, &pos, j);
    }

    p->cartes[pos].type = 'N';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = 0;
    p->cartes[pos].speciale = 0;
    pos++;

    // Initialisation des 6 cartes bonus
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = FOIS2;
    p->cartes[pos].speciale = 0;
    pos++;

    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS2;
    p->cartes[pos].speciale = 0;
    pos++;

    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS4;
    p->cartes[pos].speciale = 0;
    pos++;

    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS6;
    p->cartes[pos].speciale = 0;
    pos++;

    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS8;
    p->cartes[pos].speciale = 0;
    pos++;

    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS10;
    p->cartes[pos].speciale = 0;
    pos++;

    // Initialisation de la carte spéciale : STOP
    p->cartes[pos].type = 'S';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = 0;
    p->cartes[pos].speciale = STOP;
    pos++;
  }
  p->nbCartes = nbPaquet * FLIP7; // paquet de ... cartes
}

// Mélange les cartes du paquet
void melanger(Paquet *p) {
  int j;
  Carte tmp; // Carte temporaire pour inverser les 2 cartes

  //  - Algorithme de Fisher-Yates (mélange de knuth)
  //  - On parcourt le paquet de la fin vers le début
  //  - A chaque position i on échange la carte avec une carte  choisie
  //  aléatoirement (complexité o(N))
  for (int i = p->nbCartes - 1; i > 0; i--) {
    // formule rand() %(max-min+1) + min = Valeurs aléatoires entre 0 et i
    j = rand() % (i + 1);

    // on inverse les 2 cartes
    tmp = p->cartes[i];
    p->cartes[i] = p->cartes[j];
    p->cartes[j] = tmp;
  }
  printf("\n------------------- " EMOJI_MELANGE
         " Mélange en cours" EMOJI_MELANGE " -------------------\n");
}

// Retourne la carte en haut de la pile
Carte piocher(Paquet *p) {
  if (p == NULL || p->nbCartes == 0) {
    printf("\nErreur de programmation !\n");
    exit(ERREUR_10);
  }

  p->nbCartes = p->nbCartes - 1; // décrémente le compteur de carte
  return p->cartes[p->nbCartes]; // carte piochée
}

void carteStop(Perso *joueur, Perso *joueurs, int nbjoueur, Carte c) {
  if (nbjoueur < 3 || joueurs == NULL) {
    printf("\nErreur de programation !\n");
    exit(ERREUR_11);
  }

  if (c.type == 'S' && c.speciale == STOP) {
    char prenom[TAILLE_PRENOM];
    int enJeu = 0; // Compteur pour le nombre de joueur dans la manche
    bool trouve = false; 

    // Tant qu'aucun joueur n'est trouvé la boucle continue
    while (!trouve) {
      enJeu = 0;
      for (int i = 0; i < nbjoueur; i++) {
        if ((joueurs + i)->Ajouer == false) {
          enJeu++;
        }
      }

      // Si le joueur qui pioche la carte STOP est le seul encore en jeu il se
      // stoppe lui même
      if (enJeu <= 1) {
        printf("\n");
        printf(GRAS "\n%s vous êtes la seule personne encore en jeu par "
                    "conséquent vous vous ciblez tout seul !" EMOJI_BLESSURE
                    "\n",
               joueur->prenom);
        joueur->Ajouer = true;
        trouve = true;
        break;
      }
      // Sinon il choisit qui il veut stopper
      else {
        printf("\n%s qui veux tu stopper ? \n", joueur->prenom);
        while (scanf("%40s", prenom) != 1 || !PrenomValide(prenom)) {
          printf(RESET GRAS"\nSaisie invalide, veuillez recommencer !\n");
          while (getchar() != '\n');
        }
        while (getchar() != '\n'); // On vide le tampon d'entrée
      }

      bool nomTrouve = false;
     
      for (int i = 0; i < nbjoueur; i++) {
        if (strcmp(prenom, (joueurs + i)->prenom) == 0) {
          nomTrouve = true;
          if ((joueurs + i)->Ajouer == false &&
            strcmp((joueurs + i)->prenom, joueur->prenom) != 0) {
            printf("\n");
            printf(EMOJI_STOP GRAS
                   " %s vous avez été stoper, vous passez votre manche \n" RESET,
                   (joueurs + i)->prenom);
            (joueurs + i)->Ajouer = true;
            trouve = true;
          } else if (strcmp((joueurs + i)->prenom, joueur->prenom) == 0) {
            printf(GRAS "\nVous ne pouvez pas vous stopper vous même\n" RESET);
          } else {
            printf(GRAS "\nCe joueur a déjà joué\n" RESET);
          }
          break; // On arrête la boucle dès que le joueur est trouvé
        }
      }
      if (!nomTrouve) {
        printf(GRAS "\nCe Joueur n'existe pas \n" RESET);
      }
    }
  } else {
    return;
  }
}