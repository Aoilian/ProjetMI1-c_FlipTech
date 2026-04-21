#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FLIP7 94 /* les 94 cartes du jeu FLIP7 */

/* une carte du jeu */

typedef struct {
    char type; /* 'N' = carte numéro, 'B' = carte bonus, 'S' = carte spéciale */
    int numero;  /* de 12 à 0 */
    char* bonus; /* 6 cartes bonus */
    char* speciale; /* 9 cartes spéciales */
} Carte;

/* le paquet de cartes */

typedef struct {
    Carte cartes[FLIP7];
    int nbCartes; /* nombre de cartes restantes dans la pile */
} Paquet;

/* les statistiques */

typedef struct {
    int nbNumero; /* nombre de cartes numéro piochées */
    int nbBonus; /* nombre de cartes bonus piochées */
    int nbSpeciale; /* nombre de cartes spéciale piochées */
} Stats;

/* permet d'afficher tout le paquet pour contrôle avant et après mélange*/

void afficherPaquet(Paquet *p) {
    for (int i = 0; i < 94; i++) {
        if (p->cartes[i].type == 'N') printf("Carte numéro %d\n",p->cartes[i].numero);
        else if (p->cartes[i].type == 'B') printf("Carte bonus %s\n",p->cartes[i].bonus);
        else printf("Carte speciale %s\n",p->cartes[i].speciale);
    }
}

/* permet d'initialiser le paquet avec toutes les cartes du jeu */

void creerPaquet(Paquet *p) {
    int pos = 0; /* position dans le paquet de 0 à 93 */

    /* 79 cartes numéro */
    for (int i = 0; i < 12; i++) {
        p->cartes[i].type = 'N';
        p->cartes[i].numero = 12;
        p->cartes[i].bonus = NULL;
        p->cartes[i].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 11; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 11;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 10; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 10;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 9; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 9;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 8; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 8;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 7; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 7;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 6; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 6;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 5; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 5;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 4; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 4;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 3; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 3;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    for (int i = 0; i < 2; i++) {
        p->cartes[pos].type = 'N';
        p->cartes[pos].numero = 2;
        p->cartes[pos].bonus = NULL;
        p->cartes[pos].speciale = NULL;
        pos++;
    }
    p->cartes[pos].type = 'N';
    p->cartes[pos].numero = 1;
    p->cartes[pos].bonus = NULL;
    p->cartes[pos].speciale = NULL;
    pos++;
    p->cartes[pos].type = 'N';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = NULL;
    p->cartes[pos].speciale = NULL;
    pos++;

    /* 6 cartes bonus */
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = "*2";
    p->cartes[pos].speciale = NULL;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = "+2";
    p->cartes[pos].speciale = NULL;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = "+4";
    p->cartes[pos].speciale = NULL;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = "+6";
    p->cartes[pos].speciale = NULL;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = "+8";
    p->cartes[pos].speciale = NULL;
    pos++;
    p->cartes[pos].type = 'B';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = "+10";
    p->cartes[pos].speciale = NULL;
    pos++;

    /* 9 cartes spéciales */
    for (int i = 0; i < 3; i++) {
    p->cartes[pos].type = 'S';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = NULL;
    p->cartes[pos].speciale = "STOP";
    pos++;
    }
    for (int i = 0; i < 3; i++) {
    p->cartes[pos].type = 'S';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = NULL;
    p->cartes[pos].speciale = "TROIS A LA SUITE";
    pos++;
    }
    for (int i = 0; i < 3; i++) {
    p->cartes[pos].type = 'S';
    p->cartes[pos].numero = 0;
    p->cartes[pos].bonus = NULL;
    p->cartes[pos].speciale = "SECONDE CHANCE";
    pos++;
    }
    afficherPaquet(p); /* pour contrôle */
    printf("\n");
    p->nbCartes = FLIP7; /* nouveau paquet de 94 cartes */
}

/* permet de mélanger aléatoirement les cartes */

void melanger(Paquet *p) {
    int j;
    Carte tmp; 

    for (int i = p->nbCartes - 1; i > 0; i--) {
        /* formule rand() %(max-min+1) + min = Valeurs aléatoires entre 0 et i-1 */
        j = rand() % i ; 
        /* on inverse les 2 cartes */
        tmp = p->cartes[i];
        p->cartes[i] = p->cartes[j];
        p->cartes[j] = tmp;
    }
    afficherPaquet(p); /* pour contrôle */
}

/* retourne la carte en haut de la pile et met à jour les statistiques */

Carte piocher(Paquet *p) {
    printf("\nCartes restantes : %d\n", p->nbCartes);
    p->nbCartes = p->nbCartes - 1;
    return p->cartes[p->nbCartes]; /* carte piochée */
}

/* permet de mettre à jour les statistiques après avoir pioché p->cartes[p->nbCartes] */

void majStats(Paquet *p, Stats *s) {

    if (p->cartes[p->nbCartes].type == 'N') s->nbNumero++; /* compteur cartes numéro piochées */
    if (p->cartes[p->nbCartes].type == 'B') s->nbBonus++; /* compteur cartes bonus piochées */
    if (p->cartes[p->nbCartes].type == 'S') s->nbSpeciale++; /* compteur cartes spéciales piochées */

}

/* permet d'afficher une carte */

void afficherCarte(Carte c) {
    printf("Carte(type=%c",c.type);
    if (c.type == 'N') printf(", valeur=%d",c.numero);
    if (c.bonus) printf(", bonus=%s", c.bonus);
    if (c.speciale) printf(", speciale=%s", c.speciale);
    printf(")\n");
}

int main() {
    Paquet paquet;
    Carte c;
    Stats statistiques = {0,0,0}; /* Ne pas oublier de mettre 0 */
    
    srand(time(NULL));
    
    creerPaquet(&paquet);

    melanger(&paquet);
    
    printf("\nPaquet créé et mélangé avec %d cartes.\n", paquet.nbCartes);

    /* on pioche tant que le paquet n'est pas vide */
    
    do {
    c = piocher(&paquet);
    afficherCarte(c);
    majStats(&paquet, &statistiques);
    } while (paquet.nbCartes > 0);

    

    /* contrôle des statistiques */

    printf("\nLe paquet est vide, ");
    printf("%d cartes numéro ont été piochées, ", statistiques.nbNumero);
    printf("%d cartes bonus ont été piochées ", statistiques.nbBonus);
    printf("et %d cartes spéciales ont été piochées\n", statistiques.nbSpeciale);
    printf("Tout est correct !");

    return 0;
}



