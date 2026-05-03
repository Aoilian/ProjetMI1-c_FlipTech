#include "cartes.h"
#include "structure.h"
#include <stdio.h>


// Affiche toutes les cartes du paquet 
void afficherPaquet(Paquet *p) {
    printf("\n");
    for (int i = 0; i < FLIP7; i++) {
        if (p->cartes[i].type == 'N') {
            printf("numéro : %d | ", p->cartes[i].numero);
        } 
        else{
            printf("bonus :  %d | ", p->cartes[i].bonus);
        }
//        else if (p->cartes[i].type == 'B') printf("Carte bonus %d\n",p->cartes[i].bonus);
//        else printf("Carte speciale %d\n",p->cartes[i].speciale);
    }
}

// Initialise le paquet avec toutes les cartes du jeu 
void creerPaquet(Paquet *p) {
    int pos = 0; // position dans le paquet de 0 à 93 

    // Initialisation des 79 cartes numéro
    for (int i = 0; i < 12; i++) {
        p->cartes[i].type = 'N';
        p->cartes[i].numero = 12;
        p->cartes[i].bonus = 0;
//       p->cartes[i].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 11; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 11;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 10; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 10;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 9; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 9;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 8; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 8;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 7; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 7;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 6; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 6;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 5; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 5;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 4; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 4;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 3; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 3;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    for (int i = 0; i < 2; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 2;
        p->cartes[pos].bonus = 0;
//      p->cartes[pos].speciale = 0;
        pos++;
    }
    p->cartes[pos].type = 'N';
    p->cartes[pos].numero = 1;
    p->cartes[pos].bonus = 0;
//  p->cartes[pos].speciale = 0;
    pos++;
    p->cartes[pos].type = 'N';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = 0;
//  p->cartes[pos].speciale = 0;
    pos++;

    /* 6 cartes bonus */
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = FOIS2;
//  p->cartes[pos].speciale = 0;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS2;
//  p->cartes[pos].speciale = 0;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS4;
//  p->cartes[pos].speciale = 0;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS6;
//  p->cartes[pos].speciale = 0;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS8;
//  p->cartes[pos].speciale = 0;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = PLUS10;
//  p->cartes[pos].speciale = 0;
    pos++;

    // 9 cartes spéciales 
//    for (int i = 0; i < 3; i++) {
//    p->cartes[pos].type = 'S';
//    p->cartes[pos].numero = 0;
//   p->cartes[pos].bonus = 0;
//    p->cartes[pos].speciale = SPECIAL1;
//    pos++;
//    }
//    for (int i = 0; i < 3; i++) {
//    p->cartes[pos].type = 'S';
//    p->cartes[pos].numero = 0;
//    p->cartes[pos].bonus = 0;
//    p->cartes[pos].speciale = SPECIAL2;
//    pos++;
//    }
//    for (int i = 0; i < 3; i++) {
//    p->cartes[pos].type = 'S';
//    p->cartes[pos].numero = 0;
//    p->cartes[pos].bonus = 0;
//    p->cartes[pos].speciale = SPECIAL3;
//    pos++;
//    }
    //afficherPaquet(p); // Affichage du paquet pour vérification 
    printf("\n");
    p->nbCartes = FLIP7; // nouveau paquet de 85 cartes 
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
    printf("\n------------------- Mélange en cours -------------------\n"); // pour contrôle 
}

// Retourne la carte en haut de la pile et met à jour les statistiques 
Carte piocher(Paquet *p) {
    printf("\nCartes restantes : %d\n", p->nbCartes);
    p->nbCartes = p->nbCartes - 1;
    return p->cartes[p->nbCartes]; // carte piochée 
}

// Met à jour les statistiques après avoir pioché p->cartes[p->nbCartes] 
void majStats(Paquet *p, Stats *s) {

    if (p->cartes[p->nbCartes].type == 'N') s->nbNumero++; // compteur cartes numéro piochées 
    if (p->cartes[p->nbCartes].type == 'B') s->nbBonus++; // compteur cartes bonus piochées 
//    if (p->cartes[p->nbCartes].type == 'S') s->nbSpeciale++; // compteur cartes spéciales piochées 

}

// Affiche les détails d'une carte 
void afficherCarte(Carte c) {
    printf("Carte ");
    if (c.type == 'N') {
        printf("numero : %d",c.numero);
    }
    if (c.type == 'B'){
        printf("bonus : ");
        switch (c.bonus) {
            case 1 : printf("+2");
                     break;
            case 2 : printf("+4");
                     break;
            case 3 : printf("+6");
                     break;
            case 4 : printf("+8");
                     break;
            case 5 : printf("+10");
                     break;
            case 6 : printf("x2");
                     break;
        }
    }
//    if (c.speciale) printf(", speciale=%d", c.speciale);
    printf(")\n");
}

// int main() {
//   Paquet paquet;
//  Carte c;
//    Stats statistiques = {0,0,0}; // Ne pas oublier de mettre 0 
    
//    srand(time(NULL));
    
//    creerPaquet(&paquet);

//    melanger(&paquet);
    
//    printf("\nPaquet créé et mélangé avec %d cartes.\n", paquet.nbCartes);

    // on pioche tant que le paquet n'est pas vide 
    
//    do {
//    c = piocher(&paquet);
//    afficherCarte(c);
//    
//    } while (paquet.nbCartes > 0);

    

    /* contrôle des statistiques */

//    printf("\nLe paquet est vide, ");
//    printf("%d cartes numéro ont été piochées, ", statistiques.nbNumero);
//    printf("%d cartes bonus ont été piochées ", statistiques.nbBonus);
//    printf("et %d cartes spéciales ont été piochées\n", statistiques.nbSpeciale);
//    printf("Tout est correct !");

//    return 0;
// }    