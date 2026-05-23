#include "score.h"
#include "affichage.h"
#include "cartes.h"
#include "erreur.h"
#include "manche.h"
#include "structure.h"
#include <stdbool.h>
#include <stdio.h>

bool NomFichierValide(char *nom) {
  if (nom == NULL || nom[0] == '\0') {
    return false;
  }

  for (int i = 0; nom[i] != '\0'; i++) {
    // On interdit les séparateur pour ne pas que le fichier créer traverse des
    // répertoires et écrase un fichier déjà existant
    if (nom[i] == '/' || nom[i] == '\\' || nom[i] == '.') {
      return false;
    }
  }
  return true;
}

unsigned int AjouterBonus(unsigned int score, int bonus) {
  if (bonus < PLUS2 || bonus > FOIS2) {
    exit(ERREUR_21);
  }

  // On applique les bonus au score du joueur
  switch (bonus) {
  case PLUS2:
    return score + 2;
  case PLUS4:
    return score + 4;
  case PLUS6:
    return score + 6;
  case PLUS8:
    return score + 8;
  case PLUS10:
    return score + 10;
  case FOIS2:
    return score * 2;
  }
  return score;
}

// Calcule le score du joueur a la fin de sa manche 
void CalculScore(Perso *joueurs, Carte *main, int taille, bool doublon) {
  if (joueurs == NULL || main == NULL || taille <= 0) {
    printf("\nErreur de programmation !\n");
    exit(ERREUR_22);
  }

  if (PersoValide(*joueurs) != 0) {
    printf("\nErreur : donnée du joueurs %s corompues, le score du joueur "
           "n'est pas calculé.\n",
           joueurs->prenom);
    exit(ERREUR_23);
  }

  unsigned int somme = 0, b = 0;
  // Total de toutes las cartes numéro piochés
  for (int i = 0; i < taille; i++) {
    if (main[i].type == 'N') {
      somme += (main + i)->numero;
    }
  }
  b = somme;

  // Ajout des cartes bonus après le tour
  // On ajoute d'abord le FOIS2 puis les autres bonus
  for (int j = 0; j < taille; j++) {
    if (main[j].type == 'B' && (main + j)->bonus == FOIS2) {
      b = AjouterBonus(b, (main + j)->bonus);
    }
  }

  // On applique ensuite les autres bonus
  for (int k = 0; k < taille; k++) {
    if (main[k].type == 'B' && (main + k)->bonus != FOIS2) {
      b = AjouterBonus(b, (main + k)->bonus);
    }
  }
  if (doublon) {
    b = 0;
  }
  joueurs->score += b;
}

void VideLaMain(Perso *joueurs, int nbjoueur) {
  if (joueurs == NULL || nbjoueur < 3) {
    printf("\nErreur\n");
    exit(ERREUR_24);
  }
  for (int i = 0; i < nbjoueur; i++) {
    // On remet à 0 le nombre de carte que les joueurs possèdent quand la manche
    // est terminé
    (joueurs + i)->nbcarte = 0;
    for (int j = 0; j < MAIN; j++) {
      // On supprime la main des joueurs quand la manche est terminé
      (joueurs + i)->carte[j].numero = 0;
      (joueurs + i)->carte[j].bonus = 0;
      (joueurs + i)->carte[j].speciale = 0;
      (joueurs + i)->carte[j].type = '\0';
    }
  }
}

// Condtion de fin de partie : - Un des joueurs atteint ou dépasse le seuil de
// 200 points
//                             - Le paquet est vide
bool FinDePartie(Perso *joueurs, Paquet pioche, int nbjoueur) {
  if (joueurs == NULL || nbjoueur < 3) {
    printf("\nErreur \n");
    exit(ERREUR_25);
  }

  if (pioche.nbCartes == 0) {
    return true;
  }
  for (int i = 0; i < nbjoueur; i++) {
    if ((joueurs + i)->score >= 200) {
      return true;
    }
  }
  return false;
}

Perso *designerGagnant(Perso *joueurs, int nbjoueur) {
  if (joueurs == NULL || nbjoueur < 3) {
    printf("\nErreur\n");
    exit(ERREUR_26);
  }

  // On initialise le max et son adresse avec celle du premier joueur
  unsigned int max = joueurs->score;
  Perso *adresseMax;
  adresseMax = joueurs;

  // On fait une recherche de maximum sur le score pour renvoyer l'adresse et le
  // score du gagnant
  for (int j = 1; j < nbjoueur; j++) {
    if (joueurs[j].score > max) {
      adresseMax = &joueurs[j];
      max = joueurs[j].score;
    }
  }
  afficherGagnant(adresseMax->prenom);

  // On retourne l'adresse du joueur qui a gagné
  return adresseMax;
}

// On enregistre le Nom de chaque gagnant de la partie
void Enregistrejoueurs(Perso *a, int nbjoueur) {
  if (a == NULL || nbjoueur < 3) {
    printf("\nErreur\n");
    exit(ERREUR_27);
  }
  Perso *gagnant = designerGagnant(a, nbjoueur);
  char nomFichier[255];

  printf("\nQuel nom donnez vous au fichier ?\n ");
  while (scanf("%254s", nomFichier) != 1 || !NomFichierValide(nomFichier)) {
    printf("Saisie invalide, veuillez recommmencer");
    while (getchar() != '\n')
      ; // On vide le tampon
  }

  FILE *fichier = NULL;
  fichier = fopen(nomFichier, "a");

  if (fichier == NULL) {
    printf("\nErreur le fichier %s n'a pas pu être créer", nomFichier);
    return;
  }

  for (int i = 0; i < nbjoueur; i++) {
    char choix;

    printf(RESET "\n%s veux tu enregistrer ton score sur le fichier %s ? (oui "
                 ": O / non : N) \n",
           (a + i)->prenom, nomFichier);

    // Tant que l'utilisateur ne saisi pas 'O' ou 'N' on lui redemande son choix
    while (scanf(" %c", &choix) != 1 || (choix != 'O' && choix != 'N')) {
      printf("Saisi invalide, veuillre réessayer. \n");
      while (getchar() != '\n')
        ; // On vide le tampon après la saisi de l'utilisateur
    }
    if (choix == 'O') {
      // On affiche le joueur et on indique qu'il est vainqeur du flip tech si
      // il a gagné une partie
      if ((a + i) == gagnant) {
        fprintf(fichier, "Prenom : %s | score : %u | vainqueur du flip tech \n",
                (a + i)->prenom,
                (a + i)->score); // On enregistre le nom du gagnant de la partie
                                 // dans le fichier Fliptech.txt
      } else {
        fprintf(fichier, "Prenom : %s | score : %u \n", (a + i)->prenom,
                (a + i)->score);
      }
    }
  }
  fclose(fichier);
}
