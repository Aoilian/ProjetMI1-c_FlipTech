#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartes.h"
#include "score.h"
#include "structure.h"
#include "affichage.h"
#include "erreur.h"

void RemplirPaquetNumero (Paquet* p, int* position, int numero) {
    if(p == NULL || position == NULL || (numero < 1 || numero > 12)){
        printf("\nErreur de programation !\n");
        exit(ERREUR_21);
    }
    for(int i = 0; i < numero; i++){
        p->cartes[*position].type = 'N';
        p->cartes[*position].numero = numero;
        p->cartes[*position].bonus = 0;
        p->cartes[*position].speciale = 0;
        (*position)++;
    }
}

// Initialise le paquet avec toutes les cartes du jeu 
void creerPaquet (Paquet* p, int nbJoueurs) {
    if(p == NULL || nbJoueurs < 3){
        printf("\nErreur de programmation !\n");
        exit(ERREUR_22);
    }

    int pos = 0;
    int nbPaquet = (nbJoueurs+9)/10; 

    p->cartes = malloc(sizeof(Carte) * (nbPaquet * FLIP7));

    if(p->cartes == NULL){
        printf("Allocation échouée !");
        exit(ERREUR_6);
    }
    
    // On créer plusieurs paquet selon le nombre de joueurs
    for(int i = 0; i < nbPaquet; i++){
        // Initialisation des 79 cartes numéro
        for(int j = 1; j < 12; j++){
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

// Mélange aléatoirement les cartes du paquet
void melanger(Paquet *p) {
    int j;
    Carte tmp; // Carte temporaire pour inverser les 2 cartes

    for (int i = p->nbCartes - 1; i > 0; i--) {
        // formule rand() %(max-min+1) + min = Valeurs aléatoires entre 0 et i-1 
        j = rand() % i ; 
        // on inverse les 2 cartes 
        tmp = p->cartes[i];
        p->cartes[i] = p->cartes[j];
        p->cartes[j] = tmp;
    }
    printf("\n------------------- "EMOJI_MELANGE" Mélange en cours"EMOJI_MELANGE" -------------------\n"); 
}

// Retourne la carte en haut de la pile 
Carte piocher(Paquet *p){
    if (p == 0) {
       exit(ERREUR_7);
    }
    
    p->nbCartes = p->nbCartes - 1;
    return p->cartes[p->nbCartes]; // carte piochée 
}

void carteStop (Perso joueur, Perso* joueurs, int nbjoueur, Carte c) {
    if (nbjoueur < 3 || joueurs == NULL) {
        printf("\nErreur de programation !\n");
        exit(ERREUR_8);
    }

    if (c.type == 'S' && c.speciale == STOP) {
        char prenom[TAILLE];
        int enJeu = 0; // Compteur pour le nombre de joueur dans la manche
        bool trouve = false; 

        // Tant qu'aucun joueur n'est trouvé la boucle continue
        while (!trouve) {
            enJeu = 0;
            for( int i = 0; i < nbjoueur; i++) {
                if ((joueurs+i)->Ajouer == false) {
                    enJeu++;
                }
            }

            // Si le joueur qui pioche la carte STOP est le seul encore en jeu il se stoppe lui même
            if(enJeu <= 1){
                printf("\n");
                printf(GRAS"\n %s vous êtes la seule personne encore en jeu par conséquent vous vous ciblez tout seul !" EMOJI_BLESSURE "\n", joueur.prenom);
                strcpy(prenom, joueur.prenom); // On copie la chaîne de caractère car les tableaux ne sont pas assignable en C
            }
            // Sinon il choisit qui il veut stopper
            else{
                printf("\n%s qui veux tu stopper ? \n", joueur.prenom);
                while(scanf("%s", prenom) != 1 && !PrenomValide(prenom)){
                    printf("Saisie invalide, veuillez recommencer !");
                    while(getchar() != '\n');
                }
            }

            bool nomTrouve = false; 
            for(int i = 0; i < nbjoueur; i++){
                if(strcmp(prenom, (joueurs+i)->prenom) == 0 ){
                        nomTrouve = true;
                        if((joueurs+i)->Ajouer == false){
                            printf(EMOJI_STOP GRAS CLIGNOTE " %s vous avez été stoper, vous passez votre tour \n" RESET, (joueurs+i)->prenom);
                            (joueurs+i)->Ajouer = true;
                            trouve = true;
                        } else{
                            printf(GRAS"\nCe joueur a déjà joué\n"RESET);
                        }
                        break; // On arrête la boucle dès que le joueur est trouvé
                }
            }
            if(!nomTrouve){
                    printf(GRAS"\nCe Joueur n'existe pas \n"RESET);
            }
        }
    } else{
        return;
    }
}