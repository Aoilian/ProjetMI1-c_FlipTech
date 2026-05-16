#include <asm-generic/ioctls.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "cartes.h"
#include "erreur.h"
#include "affichage.h"
#include "structure.h"

/*
    - Récupère la largeur actuelle  du terminal ( en nombre de colonne )
    - Utilise l'appel système 'ioctl' pour interagir avec le terminal et obtenir ses dimensions
    - Renvoie la largeur du terminale ou 80 par défaut si 
*/
int largeurTerminal(){
    // Structure pour stocker les dimensions du terminal (lignes et colonnes)
    // ws_col : nombre de colonnes (entier non signé)
    struct winsize w;

    // Appel du système pour obtenir les dimensions du terminal :
    //- STDOUT_FILENO : descripteur de fichier de la sortie standrad
    //- TIOCGWINSZ : commande  pour récupérer la taille de la fenêtre du terminal
    //- Retourne 0 en cas de succès et -1 sinon
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // On verifie que la valeur récupérée est valide
    if (w.ws_col > 0){  
        return w.ws_col; 
    }

    return 80; // Valeur par défaut si l'appel échoue -> 80 est une valeur standard pour les terminaux
}

/*
    - Calcule la largeur en colonnes terminales d'une chaîne UTF-8
    - En UTF-8, certains caractères (comme les accent ou les emoji) occupent plusieurs octet mais ne doivent compter que pour 1 ou 2 colonne à l'affichage
*/
int calculeLargeurUtf8 (char* chaine) {
    int largeur = 0;

    // Parcourt la chaine de charactère jusqu'à la fin 
    while(*chaine != '\0'){

        // CAS 1 : caractère ASCII (1 octet, 1 colonne)
        // 0x80 = 10000000 en binaire -> Si le bit de poid fort est 0 c'est un caractère ASCII 
        if((*chaine & 0x80) == 0){
            
            largeur++;
            chaine++;
        } 
        // CAS 2 : caractère UTF-8 (2 octets, 1 colonne)
        // 0xE0 = 11100000 en binaire -> Si les 3 premiers bits sont 110, c'est un caractère sur 2 octets  
        else if ((*chaine & 0xE0) == 0xC0) {
            largeur++;
            chaine += 2;
        } 
        // CAS 3 : caractère UTF-8 (3 octet, 1 colonne)
        // 0xF0 = 11110000 en binaire -> Si les 4 premiers bits sont 1110, c'est un caractère sur 3 octets  
        else if ((*chaine & 0xF0) == 0xE0) {
            largeur++;
            chaine += 3;
        }  
        // CAS 4 : caractère UTF-8 (4 octet, 2 colonne)
        // 0xF0 = 11110000 en binaire -> Si les 5 premiers bits sont 11110, c'est un caractère sur 4 octets
        else{
            largeur += 2;
            chaine += 4;
        }
    }
    return largeur;
}


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
    int col = largeurTerminal();

    int espacement = (col - strlen(" F L I P T E C H - Le jeu de cartes ultime")) / 2;

    effacerEcran();
    printf("\n" V_NOIR);
    afficherSeparateur(col);
    printf(RESET CLIGNOTE  "%*s%s%*s", espacement, "", RESET EMOJI_CARTE GRAS V_NOIR " F L I P T E C H - Le jeu de cartes ultime" RESET EMOJI_CARTE,espacement, "\n" V_NOIR);
    afficherSeparateur(col);
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
    int largeurPrenom = calculeLargeurUtf8(joueur->prenom);
    int espaceRestant = 15 - largeurPrenom;
    
    if(espaceRestant < 0){
        espaceRestant = 0;
    }

    for(int i = 0; i < nbJoueurs; i++){
        if(joueurs[i].score > scoreMax){
            scoreMax = joueurs[i].score;
        }
    }

    printf("\n");
    
    if(joueur->score == scoreMax && joueur->score != 0){
        printf("\n╔═══════════════════════════════════════════╗ ");
        printf("\n║"EMOJI_SCORE" SCORE de %s = %5d pts" , joueur->prenom, joueur->score);
        for(int i = 0; i < espaceRestant-1; i++){
            printf(" ");
        }
        printf(" "EMOJI_ETOILE "  ║");
        printf("\n╚═══════════════════════════════════════════╝ \n");
    }
    else{
        printf("\n╔═══════════════════════════════════════╗ ");
        printf("\n║"EMOJI_SCORE" SCORE de %s = %5d pts", joueur->prenom, joueur->score);
        for(int i = 0; i < espaceRestant; i++){
            printf(" ");
        }
        printf("║");
        printf("\n╚═══════════════════════════════════════╝\n");
    }
}

void afficherNbcarte(Paquet* p){
    if(p == NULL){
        exit(ERREUR_17);
    }

    int restanteNum = 0, restanteBon = 0, restanteSpeciale = 0;
    int col = largeurTerminal();

    printf("\n" GRAS);
    afficherSeparateur(col);
    printf(RESET EMOJI_SCORE GRAS V_BLANC" Cartes restantes dans le paquet %d : ", p->nbCartes);
    printf("\n");

    for(int i = 0; i < 13; i++){
        restanteNum = 0;
        for(int j = 0; j < p->nbCartes; j++){
            if(p->cartes[j].type == 'N' && p->cartes[j].numero == i){
                restanteNum ++;
            }
        }
        printf(GRAS V_BLANC "[%2d:%2d]    " RESET, i , restanteNum);
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
        case PLUS2 : printf( GRAS V_BLANC"[+2: %d]    ", restanteBon);
                break;
        case PLUS4 : printf("[+4: %d]    ", restanteBon);
                break;
        case PLUS6 : printf("[+6: %d]    " , restanteBon);
                break;
        case PLUS8 : printf("[+8: %d]    ", restanteBon);
                break;
        case PLUS10 : printf("[+10:%d]    ", restanteBon);
                break;
        case FOIS2 : printf("[x2: %d]    ", restanteBon);
                break;
    }
}

    restanteSpeciale = 0;
    for(int j = 0; j < p->nbCartes; j++){
        if(p->cartes[j].type == 'S' && p->cartes[j].speciale == STOP){
            restanteSpeciale ++;
        }
    }
    printf("[STOP:%2d] " RESET, restanteSpeciale);
    printf("\n");
    afficherSeparateur(col);
}


void afficherJoueur(char* prenom){
    if(prenom == NULL){
        exit(ERREUR_18);
    }

    int largeurPrenom = calculeLargeurUtf8(prenom);
    int espaceRestant = 23 - largeurPrenom;
    
    if(espaceRestant < 0){
        espaceRestant = 0;
    }

    printf(V_NOIR "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ " RESET "" EMOJI_JOUEUR GRAS V_BLANC" A toi de jouer : %s", prenom);
    for(int i = 0; i < espaceRestant; i++){
        printf(" ");
    }
    printf(V_NOIR"┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"RESET);
}


void afficherGagnant (char* prenom) {

        int largeurPrenom = calculeLargeurUtf8(prenom);
        int espaceRestant = 23 - largeurPrenom;
        printf(V_BLANC"\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		printf(  GRAS "\n┃ Le gagnant de la partie est : %-23s " , prenom);
        for (int i = 0; i < espaceRestant; i++) {
            printf(" ");
        }
        printf(EMOJI_TROPHEE"┃\n");
        printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n" RESET);
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

