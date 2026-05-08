#include "affichage.h"
#include "structure.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void effacerEcran(){
    printf("\033[2J\033[H"); // CSI 2J = effacer, CSI H = curseur en (0,0)
}

void afficherSeparateur(int largeur){
    for(int i = 0; i < largeur; i++){
        printf("=");
    }
    printf(RESET "\n");   
}

void afficherTitrePrincipal(){
    effacerEcran();
    printf("\n");
    afficherSeparateur(50);
    printf(RESET " " EMOJI_CARTE " " CLIGNOTE GRAS V_NOIR  " F L I P T E C H - Le jeu de cartes ultime " RESET " " EMOJI_CARTE "\n" );
    afficherSeparateur(50);
    printf("\n");
}

void afficherCarteEsthetique(Carte c){
    if(c.type == 'N'){
        if(c.numero >= 10 ){
            printf(GRAS V_ROUGE "[ %2d ] " RESET, c.numero);
        }
        else if(c.numero >= 7){
            printf(GRAS V_JAUNE "[ %2d ] " RESET, c.numero);
        }
        else if(c.numero >= 4){
            printf(GRAS V_CYAN "[ %2d ] " RESET, c.numero);
        }
        else{
            printf(GRAS V_BLANC "[ %2d ] " RESET, c.numero);
        }
    }
    else if (c.type == 'B'){
        switch (c.bonus) {
            case 1 : printf(V_MAGENTA "[ +2 ] " RESET);
                     break;
            case 2 : printf(V_MAGENTA"[ +4 ] " RESET);
                     break;
            case 3 : printf(V_MAGENTA"[ +6 ] " RESET);
                     break;
            case 4 : printf(V_MAGENTA"[ +8 ] " RESET);
                     break;
            case 5 : printf(V_MAGENTA"[ +10 ] " RESET);
                     break;
            case 6 : printf(V_MAGENTA"[ x2 ] " RESET );
                     break;
        }
    }
    printf(" ");
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
    }

        printf("\n");
        
        if(joueur->score == scoreMax){
            printf("\n╔═══════════════════════════════════════════╗ ");
            printf("\n║"EMOJI_SCORE" SCORE de %-15s = %5d pts "EMOJI_ETOILE" ║" , joueur->prenom, joueur->score);
            printf("\n╚═══════════════════════════════════════════╝ \n");
        }
        else{
            printf("\n╔═══════════════════════════════════════╗ ");
            printf("\n║"EMOJI_SCORE" SCORE de %-15s = %5d pts ║  ", joueur->prenom, joueur->score);
            printf("\n╚═══════════════════════════════════════╝\n");
        }
    }


void afficherPaquet(Paquet* p){
    if(p == NULL){
        exit(32);
    }

    int total = 85;
    int restant = p->nbCartes;
    int barre = 85;
    int plein = (restant*barre)/total;
    printf("Nombre de carte restante dans le paquet : ");
    for(int i = 0; i < barre; i++){
        if(i < plein){
            printf(V_VERT""BOITE_PLEINE""RESET);
        }
        else{
            printf(V_BLANC""BOITE_M""RESET);
        }
        
    }
    printf("\n");
}


void afficherStat(Stats statistiques){
    afficherSeparateur(50);
    printf(GRAS "" EMOJI_SCORE " STATISTIQUES DE LA PARTIE : ");
    printf("\n %d cartes numéro ont été piochées, ", statistiques.nbNumero);
    printf("\n %d cartes bonus ont été piochées \n" RESET, statistiques.nbBonus);
    afficherSeparateur(50);
}