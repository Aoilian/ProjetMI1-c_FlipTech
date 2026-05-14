#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartes.h"
#include "erreur.h"
#include "affichage.h"
#include "structure.h"


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
    int espacement = (150 - strlen(" F L I P T E C H - Le jeu de cartes ultime")) / 2;

    effacerEcran();
    printf("\n" V_NOIR);
    afficherSeparateur(150);
    printf(RESET CLIGNOTE  "%*s%s%*s", espacement, "", RESET EMOJI_CARTE GRAS V_NOIR " F L I P T E C H - Le jeu de cartes ultime" RESET EMOJI_CARTE,espacement, "\n" V_NOIR);
    afficherSeparateur(150);
    printf("\n" RESET);
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
            case PLUS2 : printf(V_MAGENTA "[ +2 ] ");
                     break;
            case PLUS4 : printf("[ +4 ] ");
                     break;
            case PLUS6 : printf("[ +6 ] ");
                     break;
            case PLUS8 : printf("[ +8 ] ");
                     break;
            case PLUS10 : printf("[ +10 ] ");
                     break;
            case FOIS2 : printf("[ x2 ] ");
                     break;
        }
    }
    else{
        printf("[STOP] ");
    }
    printf(RESET " ");
}


void afficherTableauScores(Perso* joueur, Perso* joueurs, int nbJoueurs){
    if(joueurs == NULL || joueur == NULL){
        exit(ERREUR_15);
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
        exit(ERREUR_16);
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
    printf(GRAS"\n");
    afficherSeparateur(50);
    printf(GRAS "" EMOJI_SCORE " STATISTIQUES DE LA PARTIE : ");
    printf("\n %d cartes numéro ont été piochées, ", statistiques.nbNumero);
    printf("\n %d cartes bonus ont été piochées \n" RESET, statistiques.nbBonus);
    afficherSeparateur(50);
}

void afficherNbcarte(Paquet* p){
    if(p == NULL){
        exit(ERREUR_17);
    }

    int restanteNum = 0, restanteBon = 0, restanteSpeciale = 0;

    printf("\n" GRAS);
    afficherSeparateur(81);
    printf(EMOJI_SCORE GRAS" Cartes restantes dans le paquet : ");
    printf("\n");

    for(int i = 0; i < 13; i++){
        restanteNum = 0;
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
        restanteBon = 0;
        for(int j = 0; j < p->nbCartes; j++){
            if(p->cartes[j].type == 'B' && p->cartes[j].bonus == i){
                restanteBon ++;
            }
               
        }
     
        switch(i){
                case PLUS2 : printf( GRAS V_BLANC"[+2: %d] ", restanteBon);
                     break;
                case PLUS4 : printf("[+4: %d] ", restanteBon);
                     break;
                case PLUS6 : printf("[+6: %d] " , restanteBon);
                     break;
                case PLUS8 : printf("[+8: %d] ", restanteBon);
                     break;
                case PLUS10 : printf("[+10:%d] ", restanteBon);
                     break;
                case FOIS2 : printf("[x2: %d] ", restanteBon);
                     break;
        }
        
    }

  
    restanteSpeciale = 0;
    for(int j = 0; j < p->nbCartes; j++){
        if(p->cartes[j].type == 'S' && p->cartes[j].numero == STOP){
            restanteSpeciale ++;
        }
    }
    printf(GRAS V_BLANC"[STOP:%2d] ", restanteSpeciale);
    printf(RESET GRAS"\n");
    afficherSeparateur(81);
}


void afficherJoueur(char* prenom){
    if(prenom == NULL){
        exit(ERREUR_18);
    }

    printf(V_NOIR "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ " RESET "" EMOJI_JOUEUR GRAS V_BLANC" A toi de jouer : %-23s"V_NOIR"┃\n" RESET, prenom);
    printf(V_NOIR"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"RESET);
}


void afficherGagnant(char* prenom, unsigned int score){
        printf(V_BLANC"\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		printf(  GRAS "\n┃ Le gagnant de la partie est : %-5s avec un score de %u ",prenom, score);
		                                                           printf(EMOJI_TROPHEE"        ┃\n");
	             printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}


void afficherStatut (Perso* joueurs, int nbJoueurs) {
    if(joueurs == NULL){
        exit(ERREUR_19);
    }

    printf("%s\n", ITALIC "\nSTATUT DES JOUEURS DANS LA PARTIE :\n");
    for(int i = 0; i < nbJoueurs; i++){       
        if(joueurs[i].Ajouer == false){
            printf(ITALIC V_VERT"►►► %s ◄◄◄ " RESET, joueurs[i].prenom );
        }
        else{
            printf(ITALIC V_ROUGE"►►► %s ◄◄◄ " RESET, joueurs[i].prenom );
        }
    }
     printf("\n\n");
}

void afficheRegle(){
     #ifdef __WIN64__   
            system("start regle.txt");
      #elif __APPLE__   
            system("open regle.txt");
     #else
            system("xdg-open regle.txt");
     #endif
}