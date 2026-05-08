#include "affichage.h"
#include "structure.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void effacerEcran(){
    printf("\033[2J\033[H"); // CSI 2J = effacer, CSI H = curseur en (0,0)
}

void afficherSeparateur(int largeur){
    printf(GRAS CYAN);
    for(int i = 0; i < largeur; i++){
        printf("=");
    }
    printf(RESET "\n");   
}

void afficherTitrePrincipal(){
    effacerEcran();
    printf("\n");
    afficherSeparateur(60);
    printf(RESET " " EMOJI_CARTE " " GRAS V_JAUNE " F L I P T E C H - Le jeu de cartes ultime " RESET " " EMOJI_CARTE "\n" );
    afficherSeparateur(60);
    printf("\n");
}

void afficherCarteEsthetique(Carte c){
    if(c.type == 'N'){
        if(c.numero >= 10 ){
            printf(GRAS V_ROUGE "carte piochée : [ %2d ]" RESET "\n", c.numero);
        }
        else if(c.numero >= 7){
            printf(GRAS V_JAUNE "carte piochée : [ %2d ]" RESET "\n", c.numero);
        }
        else if(c.numero >= 4){
            printf(GRAS V_CYAN "carte piochée : [ %2d ]" RESET "\n", c.numero);
        }
        else{
            printf(GRAS V_BLANC "carte piochée : [ %2d ]" RESET "\n", c.numero);
        }
    }
}

void afficherTableauScores(Perso* joueur, Perso* joueurs, int nbJoueurs){
    if(joueurs == NULL || joueur == NULL){
        exit(10);
    }

    unsigned int scoreMax = 0;
    

    for(int i = 0; i < nbJoueurs; i++){
        if(joueurs[i].score > scoreMax){
            scoreMax = joueurs[i].score;
        }

        printf("\n");
        
        if(joueur->score == scoreMax){
            printf("\n╔═══════════════════════════════════════╗ ");
            printf("\n║"EMOJI_SCORE" SCORE de %-15s = %5d pts ║  " EMOJI_ETOILE "", joueur->prenom, joueurs[i].score);
            printf("\n╚════════════════════════════════════════╝");
        }
        else{
            printf("\n╔═══════════════════════════════════════╗ ");
            printf("\n║"EMOJI_SCORE" SCORE de %-15s = %5d pts ║  ", joueur->prenom, joueurs[i].score);
            printf("\n╚════════════════════════════════════════╝");
        }
    }
}

void afficherPaquet(Paquet* p){
    if(p == NULL){
        
    }
}