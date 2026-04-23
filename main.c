#include "cartes.h"

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



