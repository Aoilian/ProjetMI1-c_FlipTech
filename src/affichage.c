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
            case 1 : printf(V_MAGENTA "[ +2 ] ");
                     break;
            case 2 : printf("[ +4 ] ");
                     break;
            case 3 : printf("[ +6 ] ");
                     break;
            case 4 : printf("[ +8 ] ");
                     break;
            case 5 : printf("[ +10 ] ");
                     break;
            case 6 : printf("[ x2 ] ");
                     break;
        }
    }
    printf(RESET " ");
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
            printf("\n║"EMOJI_SCORE" SCORE de %-14s = %5d pts" , joueur->prenom, joueur->score);
            printf(" "EMOJI_ETOILE "  ║");
            printf("\n╚═══════════════════════════════════════════╝ \n");
        }
        else{
            printf("\n╔═══════════════════════════════════════╗ ");
            printf("\n║"EMOJI_SCORE" SCORE de %-15s = %5d pts║  ", joueur->prenom, joueur->score);
            printf("\n╚═══════════════════════════════════════╝\n");
        }
    }


void afficherPaquet(Paquet* p){
    if(p == NULL){
        exit(32);
    }

    int total = 85;
    int restant = p->nbCartes;
    int barre = 42;
    int plein = (restant*barre)/total;
    printf("Il reste %d cartes dans le paquet :  ",p->nbCartes);
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
    printf("\n");
    afficherSeparateur(50);
    printf(GRAS "" EMOJI_SCORE " STATISTIQUES DE LA PARTIE : ");
    printf("\n %d cartes numéro ont été piochées, ", statistiques.nbNumero);
    printf("\n %d cartes bonus ont été piochées \n" RESET, statistiques.nbBonus);
    afficherSeparateur(50);
}

void afficherNbcarte(Paquet* p){
    printf(GRAS"\n");
    afficherSeparateur(79);
    printf(EMOJI_SCORE " Cartes restantes dans le paquet : ");
    printf("\n");
    for(int i = 0; i < 13; i++){
        int restanteNum = 0;
        for(int j = 0; j < p->nbCartes; j++){
            if(p->cartes[j].type == 'N' && p->cartes[j].numero == i){
                restanteNum ++;
            }
        }
        printf(GRAS V_BLANC"[%2d:%2d] ", i , restanteNum);
        if(i == 9){
            printf("\n");
        }
    }
    
    for(int i = 1; i < 7; i++){
        int restanteBon = 0;
        for(int j = 0; j < p->nbCartes; j++){
            if(p->cartes[j].type == 'B' && p->cartes[j].numero == i){
                restanteBon ++;
            }
        }
        switch(i){
                case 1 : printf( GRAS V_BLANC"[+2: %d] ", restanteBon);
                     break;
                case 2 : printf("[+4: %d] ", restanteBon);
                     break;
                case 3 : printf("[+6: %d] " , restanteBon);
                     break;
                case 4 : printf("[+8: %d] ", restanteBon);
                     break;
                case 5 : printf("[+10:%d] ", restanteBon);
                     break;
                case 6 : printf("[x2: %d] ", restanteBon);
                     break;
        }
        
    }
    printf(RESET GRAS"\n");
    afficherSeparateur(79);
   
}

void afficherGagnant(char* prenom, unsigned int score){
        printf(V_BLANC"\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		printf(  GRAS "\n┃ Le gagnant de la partie est : %-5s avec un score de %u ",prenom, score);
		                                                           printf(EMOJI_TROPHEE"        ┃\n");
	             printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}