#include "cartes.h"
#include "structure.h"
#include "affichage.h"


// Initialise le paquet avec toutes les cartes du jeu 
void creerPaquet(Paquet *p, int nbJoueurs) {
    
    int pos = 0; // position dans le paquet
    int nbPaquet = (nbJoueurs+9)/10; 

    p->cartes = malloc(sizeof(Carte) * (nbPaquet * FLIP7));

    if(p->cartes == NULL){
        printf("Allocation échouée !");
        exit(16);
    }
    for(int i = 0; i < nbPaquet; i++){
    // Initialisation des 79 cartes numéro
        for (int i = 0; i < 12; i++) {
            p->cartes[i].type = 'N';
            p->cartes[i].numero = 12;
            p->cartes[i].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 11; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 11;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 10; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 10;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 9; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 9;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 8; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 8;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 7; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 7;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 6; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 6;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 5; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 5;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 4; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 4;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 3; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 3;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        for (int i = 0; i < 2; i++) {
            p->cartes[pos].type = 'N';
            p->cartes[pos].numero = 2;
            p->cartes[pos].bonus = 0;
            pos++;
        }
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 1;
        p->cartes[pos].bonus = 0;
        pos++;

        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = 0;
        pos++;

        /* 6 cartes bonus */
        p->cartes[pos].type = 'B';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = FOIS2;
        pos++;

        p->cartes[pos].type = 'B';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = PLUS2;
        pos++;

        p->cartes[pos].type = 'B';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = PLUS4;
        pos++;

        p->cartes[pos].type = 'B';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = PLUS6;
        pos++;

        p->cartes[pos].type = 'B';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = PLUS8;
        pos++;

        p->cartes[pos].type = 'B';
        p->cartes[pos].numero = 0;
        p->cartes[pos].bonus = PLUS10;
        pos++;

        
    } 
    p->nbCartes = nbPaquet * FLIP7; // paquet de ... cartes
}

// Mélange aléatoirement les cartes du paquet
void melanger(Paquet *p) {
    int j;
    Carte tmp; 

    for (int i = p->nbCartes - 1; i > 0; i--) {
        // formule rand() %(max-min+1) + min = Valeurs aléatoires entre 0 et i-1 
        j = rand() % i ; 
        // on inverse les 2 cartes 
        tmp = p->cartes[i];
        p->cartes[i] = p->cartes[j];
        p->cartes[j] = tmp;
    }
    printf("\n------------------- "EMOJI_MELANGE" Mélange en cours"EMOJI_MELANGE" -------------------\n"); // pour contrôle 
}

// Retourne la carte en haut de la pile 
Carte piocher(Paquet *p){
    if(p == 0){
       exit(12);
    }
    else{
        p->nbCartes = p->nbCartes - 1;
        return p->cartes[p->nbCartes]; // carte piochée 
    }
}

// Met à jour les statistiques après avoir pioché p->cartes[p->nbCartes] 
void majStats(Carte n, Stats *s) {

    if (n.type == 'N'){
            s->nbNumero++; // compteur cartes numéro piochées
    }  
    if (n.type == 'B'){
             s->nbBonus++; // compteur cartes bonus piochées 
    }
}