#include "affichage.h"
#include "cartes.h"
#include "erreur.h"
#include "score.h"
#include "structure.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

bool PrenomValide(char *prenom) {
  if (prenom == NULL || prenom[0] == '\0') {
    return false;
  }

  unsigned char *s = (unsigned char *)prenom; // S lit chaque octet de prenom comme un nombre entre 0 et 255 car les UTF8 sont des caractères qui dépasse la valeur 127 d'un char

  while (*s != '\0') {

    // Caractère ASCII simple (ex: a, b, Z)
    if (*s < 0x80) {
      if ((*s < 'A' || *s > 'Z') && (*s < 'a' || *s > 'z')) {
        return false; // ni lettre majuscule ni minuscule -> refusé
      }
      s++; // on avance d'1 octet
    }

    /* On décode le caractère UTF-8 pour obtenir sa valeur réelle */
    // On accepte uniquement les lettres accentuée européenne (ex: é, à, ü)
    // Dans le teableau Unicode chaque caractère a un numero unique
    // Problème : UTF-8 ne stocke pas directement ce numero, il le decoupe en
    // morceaux et le rapartit en plusieurs  octets. Exemple : octet 1 : 0xC3 → on extrait le morceau 1  →  3
    //                                                         octet 2 : 0xA9 → on extrait le morceau 2  → 41
    // Réassemblage : (3 × 64) + 41 = 192 + 41 = 233 = numéro Unicode de é
    // Une fois qu'on a ce numéro, on peut vérifier si le caractère est dans la
    // plage des lettres autorisées (0x00C0 à 0x017F)
    else if (*s >= 0xC2 && *s <= 0xD9) {
      // On décale les bits du 1er octets de 6 cases vers la gauche pour
      // reserver de la place pour les bits du 2ème octet En binaire, decaler
      // vers la gauche de N position revient à multiplier la valeur initiale
      // par 2^N
      // << 6 = multiplier par 2^6
      // Exemple : avec bit1 = 3 (Avant decalage : 00000011 | Après le décalage
      // : 11000000)
      unsigned int bit1 = *s & 0x1F;
      unsigned int bit2 = *(s + 1) & 0x3F;
      unsigned int valeur = (bit1 << 6) | bit2; // On colle les 2 morceuax

      // Plage des lettres accentuées acceptées : U+00C0 (À) à U+017F (ſ)
      if (valeur < 0x00C0 || valeur > 0x017F) {
        return false; // ex: § (U+00A7) -> refusé
      }
      s += 2; // on avance de 2 octets
    }

    // Tout autre caractère (emoji, symboles chinois...) -> refusé
    else {
      return false;
    }
  }
  return true;
}

bool PrenomDejaUtilise(Perso *joueurs, char *prenom, int nbjoueurActuel) {
  if (joueurs == NULL || prenom == NULL) {
    printf("\nErreur de programmation !\n");
    exit(ERREUR_13);
  }
  for (int i = 0; i < nbjoueurActuel; i++) {
    if (strcmp(joueurs[i].prenom, prenom) == 0) {
      return true;
    }
  }
  return false;
}

// Verifie que les données d'un joueur est valide
int PersoValide(Perso a) {
  for (unsigned int i = 0; i < a.nbcarte; i++) {
    if (a.carte[i].type == 'N' &&
        (a.carte[i].numero < 0 || a.carte[i].numero > 12)) {
      return -1;
    } else if (a.carte[i].type == 'B' &&
               (a.carte[i].bonus < PLUS2 || a.carte[i].bonus > FOIS2)) {
      return -1;
    } else if (a.carte[i].type == 'S' && (a.carte[i].speciale != STOP)) {
      return -1;
    }
  }
  if (a.nbcarte > MAIN) {
    return -1;
  } else if (PrenomValide(a.prenom) == false) {
    return -1;
  }
  return 0;
}

// Demande au joueur si il veut piocher ?
void Decision(int *decision, Perso *joueur) {
  if (decision == NULL || joueur == NULL) {
    exit(ERREUR_14);
  }
  int valide = 0;

  do {
    printf("\nVoulez-vous piocher ? \n- oui : 1 \n- non : 0\n");

    // verification si scanf a bien marché, et si le nombre est respecté
    if (scanf("%d", decision) == 1 && (*decision == 0 || *decision == 1)) {
      valide = 1; // si c'est valide, c'est fini
    } else {
      printf("\nErreur : Saisie invalide.\n");
      // On vide le tampon au cas où l'utilisateur aurais tapé un caractère
      while (getchar() != '\n')
        ;
    }

  } while (valide == 0); // On recommence tant que ce n'est pas valide
}

void AfficherRegle() {
  printf(GRAS V_BLANC "\n\nRègles du jeu : FlipTech ou --flip7--\n\n");
  printf("Le Flip7 est un jeu de cartes mêlant hasard, statistiques et prise "
         "de risque. Il peut être joué à autant de joueurs que l’on souhaite "
         "(3 joueurs minimum).\n");
  printf("\nObjectif du jeu\nAccumuler le plus de points possible au fil des "
         "manches.\n");
  printf("Les cartes numéros rapportent leur valeur, et les cartes bonus "
         "modifient le score final (multiplication ou ajout)\n");
  printf("\nComposition du jeu\nLe jeu contient 85 cartes (ou plus selon le "
         "nombre de joueurs) :\n");
  printf("- 79 cartes numéros allant de 0 à 12, avec une quantité croissante "
         "selon le numéro (ex : 1 carte “0”, 12 cartes “12”)\n");
  printf("- 6 cartes bonus : x2, +2, +4, +6, +8, +10\n");
  printf("- Une carte spéciale : STOP, qui permet de stopper un autre joueur "
         "de la partie quand on la pioche\n");
  printf("\nDéroulement d’une manche\n");
  printf("Les joueurs jouent dans le même ordre, chacun leur tour.\n");
  printf("À son tour, un joueur peut :\n1) S'arrêter : Il conserve les points "
         "déjà accumulés dans la manche\n2) Piocher une carte (4 situations "
         "possibles) :\n");
  printf("Nouvelle carte numéro →  Elle s’ajoute à sa collection et augmente "
         "son score de manche.\nCarte bonus → Son effet s’appliquera au score "
         "final de la manche.\n");
  printf("Carte numéro déjà obtenue → Le joueur perd la manche et marque 0 "
         "point.\n7 cartes différentes obtenues → La manche s’arrête "
         "immédiatement pour tout le monde + Le joueur gagne +15 points bonus "
         "pour avoir fait un flip7.\n");
  printf("\nFin de manche\nUne manche se termine lorsque :\nun joueur obtient "
         "7 cartes différentes,ou tous les joueurs se sont arrêtés,ou tous les "
         "joueurs restants ont perdu en tirant un doublon\n");
  printf("\nFin de partie\nLa partie s’arrête si : \n- un joueur atteint 200 "
         "points ou plus\nLe joueur avec le score total le plus élevé remporte "
         "la partie.\n");
  printf("- si la pioche est épuisée (dans ce cas, le bonus de 15 points n’est "
         "accordé que si le dernier joueur a bien obtenu 7 cartes "
         "différentes).\n\n\n"RESET);
}

void VoirRegle() {
  int lire = 0, valide = 0;
  do {
    printf(RESET V_BLANC"Voulez-vous consulter les rêgles du jeu avant de commencer la partie ?\n- Oui : 1 \n- Non : 0\n");
    if (scanf("%d", &lire) == 1 && (lire == 0 || lire == 1)) {
      valide = 1; // si c'est valide, c'est fini
    } else {
      printf("\nErreur : Saisie invalide.\n");
      // On vide le tampon au cas où l'utilisateur aurais tapé un caractère
      while (getchar() != '\n')
        ;
    }
  } while (valide == 0);
  if (lire == 1) {
    effacerEcran();
    AfficherRegle();
  }
}

// Demande le nombre de joueur dans la partie
void nmbJoueurs(int *nbJoueurs) {
  if (nbJoueurs == NULL) {
    exit(ERREUR_15);
  }
  int valide = 0;
  do {
    printf(RESET V_BLANC "\nCommençons, combien il y a t-il de joueurs dans la partie ?" EMOJI_JOUEUR "\n");
    if (scanf("%d", nbJoueurs) == 1 && (*nbJoueurs >= 3)) {
      valide = 1;
      while (getchar() != '\n')
        ; // On vide le tampon au cas où l'utilisateur aurais tapé un caractère
    } else {
      printf("\nErreur : saisie invalide.\n");
      while (getchar() != '\n')
        ; // On vide le tampon au cas où l'utilisateur aurais tapé un caractère
    }
  } while (valide == 0);
}

bool Flip7(Perso joueur) {
  int num = 0;
  for (unsigned int i = 0; i < joueur.nbcarte; i++) {
    // Seuls les cartes numéro compte pour le flip7
    if (joueur.carte[i].type == 'N') {
      num++;
    }
  }
  if (num == 7 && joueur.doublon == false) {
    return true;
  } else {
    return false;
  }
}

bool Doublon(Perso *joueur) {
  if (joueur == NULL) {
    printf("\nErreur de programmation !\n");
    exit(ERREUR_16);
  }

  for (unsigned int i = 0; i < joueur->nbcarte; i++) {
    // Si on tombe sur une carte bonus ou speciale on passe à la prochaine
    // itération car seules les cartes numéros comptent comme des doublons
    if (joueur->carte[i].type != 'N') {
      continue;
    }
    for (unsigned int j = 0; j < joueur->nbcarte; j++) {
      if (i == j) {
        continue; // On passe à la prochaine itération directement
      }
      if (joueur->carte[i].type == joueur->carte[j].type &&
          (joueur->carte[i].numero == joueur->carte[j].numero)) {
        joueur->doublon = true;
        return true;
      }
    }
  }
  return false;
}

// La manche est terminé si chacun des joueurs
bool MancheTerminee(Perso *joueurs, int nbJoueurs) {
  if (joueurs == NULL || nbJoueurs < 3) {
    printf("\n Données invalide, erreur de programation ! \n");
    exit(ERREUR_17);
  }
  for (int i = 0; i < nbJoueurs; i++) {
    if ((joueurs + i)->Ajouer == false) {
      return false;
    }
  }
  return true;
}

void preparerNouvelleManche(Perso *Joueurs, int nbJoueurs, Paquet *paquet, int compteur) {
  if (Joueurs == NULL || paquet == NULL) {
    exit(ERREUR_18);
  }
  for (int i = 0; i < nbJoueurs; i++) {
    Joueurs[i].Ajouer = false; // Tout le monde peut à nouveau jouer
    Joueurs[i].doublon = false;
  }
  VideLaMain(Joueurs, nbJoueurs);
  if (!FinDePartie(Joueurs, *paquet, nbJoueurs) && paquet->nbCartes > 0) {
    printf(GRAS "\n---------------------------  C'est parti pour la manche %d  "
                "---------------------------\n" RESET,
           compteur);
  }
}

// Gère le déroulement d'une manche :
// - Le joueur de départ est tiré aléatoirement
// - Les joueurs jouent à tour de rôle
// - La manche s'arrête si : tous les joueurs ont finis de jouer, un flip7 est réalisé ou le paquet est vide
void lancerManche(Perso *Joueurs, int nbJoueurs, Paquet *paquet) { // Joueurs => tous les joueurs de la partie
  if (Joueurs == NULL || paquet == NULL) {
    exit(ERREUR_19);
  }

  int joueurActuel = rand() % nbJoueurs;
  int decision = 0;

  // Variable colonne qui stocke la largeur du terminale
  int col = largeurTerminal();

  bool flip_7 = false;

  printf("\n-------- LE TOUR COMMENCE --------\n");
  printf("Attention : Pour le premier tour, vous êtes obligé de piocher : vous n'avez donc pas le choix !");
  sleep(3);

  // boucle du tour : tant que tout le monde n'a pas fini son tour ou qu'un
  // joueur n'a pas fait de flip7 ou que la paquet de cartes n'est pas vide on
  // continue le tour
  while (!MancheTerminee(Joueurs, nbJoueurs) && !flip_7 &&
         paquet->nbCartes > 0) {

    // On ne fait jouer le joueur que s'il n'a pas encore joué
    if (Joueurs[joueurActuel].Ajouer == false) {

      afficherSeparateur(col);
      afficherStatut(Joueurs, nbJoueurs);
      afficherSeparateur(col);

      afficherJoueur(Joueurs[joueurActuel].prenom);
      if (Joueurs[joueurActuel].nbcarte > 0 &&
          Joueurs[joueurActuel].nbcarte < MAIN) {
        printf("\n");
        printf("\nVoici ta main (%s) :  \n", Joueurs[joueurActuel].prenom);
        for (unsigned int i = 0; i < Joueurs[joueurActuel].nbcarte; i++) {
          afficherCarteEsthetique(Joueurs[joueurActuel].carte[i]);
        }
      }
      afficherNbcarte(paquet);

      // Cas 1 : la main du joueur est pleine sa manche est terminée
      // Cas 2 : la main du joueur est vide il est obligé de piocher
      if (Joueurs[joueurActuel].nbcarte >= MAIN) {
        printf("\nVotre main est pleine, vous ne pouvez plus jouer");
        Joueurs[joueurActuel].Ajouer = true;
      } else if (Joueurs[joueurActuel].nbcarte == 0) {
        Carte b = piocher(paquet);
        Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = b;
        Joueurs[joueurActuel].nbcarte++;

        printf("\nCarte piochée : ");
        afficherCarteEsthetique(b);
        carteStop(&Joueurs[joueurActuel], Joueurs, nbJoueurs, b);
        printf("\n");
        sleep(2);
        tcflush(STDIN_FILENO,TCIFLUSH); // Vide tout ce qui a été tapé pendant le sleep
      } else {
        // Cas 3 : le joueur choisit de piocher ou s'arrêter
        Decision(&decision, &Joueurs[joueurActuel]);
        if (decision == 1) {
          Carte c = piocher(paquet);
          Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = c;
          Joueurs[joueurActuel].nbcarte++;

          printf("\nCarte piochée : ");
          afficherCarteEsthetique(c);

          carteStop(&Joueurs[joueurActuel], Joueurs, nbJoueurs, c);
          printf("\n");

          // Cas 3a : le joueur pioche une carte qu'il a déjà dans sa main -> il
          // est eliminé de la manche et ne marque pas de point
          if (Doublon(&Joueurs[joueurActuel])) {
            printf("\nVous possédez déjà cette carte dans votre paquet... Vous "
                   "êtes malheureusement éliminer de la manche\n");
            Joueurs[joueurActuel].doublon = true;
            Joueurs[joueurActuel].Ajouer = true;
          }
          // Cas 3b : Un jouer fais un flip7 (7 cartes numéro différente) -> la
          // manche s'arrête pour tout le monde et le joueur prend un bonus de
          // +15 points
          if (Flip7(Joueurs[joueurActuel])) {
            printf("Bravo, %s a fait un flip 7 ! La manche est terminé et %s "
                   "la gagne avec 15 points supplémentaires !\n",
                   Joueurs[joueurActuel].prenom, Joueurs[joueurActuel].prenom);
            Joueurs[joueurActuel].score += 15;
            flip_7 = true;
          }
        } else {
          // Cas 3c : le joueur décide de s'arrêter volontairement -> il garde
          // le score qu'il avait accumulé jusqu'à préssent et sa manche se
          // termine
          printf(GRAS "\nC'est la fin de la manche pour toi !\n" RESET);
          Joueurs[joueurActuel].Ajouer = true;
        }
      }
    }
    // On passe au joueur suivant
    joueurActuel = (joueurActuel + 1) % nbJoueurs;

    if (paquet->nbCartes == 0) {
      printf(
          "\nIl n'y a plus de cartes dans le paquet, la partie prend fin !\n");
    }
  }
}

void InitialiseJoueurs(Perso *joueurs, int nbjoueur) {
  if (joueurs == NULL) {
    exit(ERREUR_20);
  }

  for (int i = 0; i < nbjoueur; i++) {
    bool valide = false;
    printf("\n--- Joueur %d ---\n", i + 1);

    do {
      printf("Prenom (20 caractères max): ");
      scanf("%40s", joueurs[i].prenom);
      while (getchar() != '\n')
        ; // on vide le tampon

      if (!PrenomValide(joueurs[i].prenom)) {
        printf("\nSaisie invalide, veuillez recommencer\n");
      } else if (PrenomDejaUtilise(joueurs, joueurs[i].prenom, i)) {
        printf("\nCe prenom est déjà utilisé !\n\n");
      } else {
        valide = true;
      }
    } while (!valide);

    // initialisation du score, nombre de carte, cartes, etc
    joueurs[i].score = 0;
    joueurs[i].nbcarte = 0;
    joueurs[i].Ajouer = false;
    joueurs[i].doublon = false;
    for (int j = 0; j < MAIN; j++) {
      joueurs[i].carte[j].type = '\0';
      joueurs[i].carte[j].numero = 0;
      joueurs[i].carte[j].bonus = 0;
      joueurs[i].carte[j].speciale = 0;
    }
  }
  for (int i = 0; i < nbjoueur; i++) {
    // On tronque le prénom saisie par l'utilisateur pour qu'il ne dépasse pas
    // les 20 caractères
    TronquerUTF8((joueurs + i)->prenom, 20);
  }
}
