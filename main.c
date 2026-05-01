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

    // tableux pour savoir si un joueur a fait un doublon ou pas pendant la manche
    bool doublon[nbJoueurs];
    
    // Initialisation du paquet 
    creerPaquet(&paquet);
    melanger(&paquet);

    // Boucle de jeu
    while(!FinDePartie(joueurs, paquet, nbJoueurs)){
            lancerManche(joueurs, nbJoueurs, &paquet, &nbpioche, doublon);
            for(int i = 0; i < nbJoueurs; i++){
                    CalculScore(&(joueurs[i]), joueurs[i].carte, joueurs[i].nbcarte, doublon[i]);
                    printf("\n%s a un score de %u \n", joueurs[i].prenom, joueurs[i].score);
            }
            preparerNouvelleManche(joueurs, nbJoueurs, &paquet);
            majStats(&paquet, &statistiques);
    }
    
    // Fin de partie  
    designerGagnant(joueurs, nbJoueurs);
    Enregistrejoueurs (joueurs, nbJoueurs);

    free(joueurs);
    return 0;
}
