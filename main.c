#include "structure.h"
#include "cartes.h"
#include "manche.h"
#include "score.h"
#include <stdlib.h>
#include <time.h>

int main() {
    // On crée une nouvelle graine pour que les mélange ne soient pas les mêmes à chaque manche
    srand(time(NULL));
    
    Paquet paquet;
    Stats statistiques = {0,0,0}; 
    int nbJoueurs, nbpioche;
    Perso* joueurs;
   
    // Saisie des joueurs
    nmbJoueurs(&nbJoueurs);
    joueurs = malloc(sizeof(Perso) * nbJoueurs);
    enregistrerJoueurs(joueurs, nbJoueurs);
    for(int j = 0; j < nbJoueurs; j++){
            Maj((joueurs+j)->prenom);
            Min((joueurs+j)->prenom);
    }
    
    // Initialisation du paquet 
    creerPaquet(&paquet);
    melanger(&paquet);

    // Boucle de jeu
    while(!FinDePartie(joueurs, paquet, nbJoueurs)){
            lancerManche(joueurs, nbJoueurs, &paquet, &nbpioche);
            for(int i = 0; i < nbJoueurs; i++){
                    CalculScore(&joueurs[i], joueurs[i].carte, joueurs[i].nbcarte);
                    printf("\n%s a un score de %u \n", joueurs[i].prenom, joueurs[i].score);
            }
            reinitialiserJoueur(joueurs, nbJoueurs);
            majStats(&paquet, &statistiques);
    }
    
    // Fin de partie  
    designerGagnant(joueurs, nbJoueurs);
    Enregistrejoueurs (joueurs, nbJoueurs);

    free(joueurs);
    return 0;
}
