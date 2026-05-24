#include "affichage.h"
#include "cartes.h"
#include "erreur.h"
#include "manche.h"
#include "score.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

int main() {
  printf("\x1b[8;40;155t"); // Force la taille du terminal
  fflush(stdout);
  sleep(1);
  tcflush(STDIN_FILENO,
          TCIFLUSH); // Vide toute saisie qui a été taper par l'utilisateur pendant le sleep

  // On crée une nouvelle graine pour que le mélange des cartes ne soient pas le même à chaque partie
  srand(time(NULL));

  Paquet paquet;
  Perso *joueurs = NULL;
  int nbJoueurs = 0, compteur = 2;

  effacerEcran();
  afficherTitrePrincipal();

  VoirRegle();

  // Saisie du nombre de joueurs
  nmbJoueurs(&nbJoueurs);
  joueurs = malloc(sizeof(Perso) * nbJoueurs);
  if (joueurs == NULL) {
    printf("\nAllocation échouée !\n");
    exit(ERREUR_12);
  }

  // Initialisation des joueurs
  InitialiseJoueurs(joueurs, nbJoueurs);

  // Initialisation du paquet
  creerPaquet(&paquet, nbJoueurs);
  melanger(&paquet);

  // Boucle de jeu
  while (!FinDePartie(joueurs, paquet, nbJoueurs)) {
    lancerManche(joueurs, nbJoueurs, &paquet);
    for (int i = 0; i < nbJoueurs; i++) {
      if (joueurs[i].nbcarte > 0) {
        CalculScore(&(joueurs[i]), joueurs[i].carte, joueurs[i].nbcarte,
                    joueurs[i].doublon);
      }
    }
    for (int j = 0; j < nbJoueurs; j++) {
      afficherTableauScores(&joueurs[j], joueurs, nbJoueurs);
    }
    sleep(3); // Pause de 3 secondes
    tcflush(STDIN_FILENO,
            TCIFLUSH); // Vide tout ce qui a été tapé pendant le sleep
    preparerNouvelleManche(joueurs, nbJoueurs, &paquet, compteur);
    compteur++;
  }

  GererEgalite(joueurs, nbJoueurs, &paquet,
               &compteur); // On gère les éventuelles égalité si il y en a fin de partie 
  Enregistrejoueurs(joueurs, nbJoueurs);  // on affiche le gagnant et on demande aux joueurs s'ils veulent enregistrer leur score

  // on libère l'espace alloué pour les joueurs et le paquet
  free(joueurs);
  free(paquet.cartes);
  return 0;
}