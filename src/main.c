#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>   
#include "erreur.h"
#include "structure.h"
#include "affichage.h"
#include "cartes.h"
#include "manche.h"
#include "score.h"

int main() {
    printf("\x1b[8;40;120t"); // Force la taille du terminale
    fflush(stdout);
    
    

    // On crée une nouvelle graine pour que le mélange des cartes ne soient pas les mêmes à chaque partie
    srand(time(NULL));
    
    Paquet paquet;
    Perso* joueurs = NULL;
    int nbJoueurs = 0, compteur = 2;
    
    effacerEcran();
    afficherTitrePrincipal();
    printf(RESET);
    

    VoirRegle();
   

    // Saisie des joueurs
    nmbJoueurs(&nbJoueurs);
    joueurs = malloc(sizeof(Perso) * nbJoueurs);
    if(joueurs == NULL){
        printf("\nAllocation échouée !\n");
        exit(ERREUR_23);
    }

    InitialiseJoueurs(joueurs, nbJoueurs);
    
    // Initialisation du paquet 
    creerPaquet(&paquet,nbJoueurs);
    melanger(&paquet);

    // Boucle de jeu
    while(!FinDePartie(joueurs, paquet,  nbJoueurs)){
            lancerManche(joueurs, nbJoueurs, &paquet);
            for(int i = 0; i < nbJoueurs; i++){
                if(joueurs[i].nbcarte > 0){
                    CalculScore(&(joueurs[i]), joueurs[i].carte, joueurs[i].nbcarte, joueurs[i].doublon);
                }
            }
            for (int j = 0; j < nbJoueurs; j++) {
                afficherTableauScores(&joueurs[j], joueurs, nbJoueurs);
            }
            sleep(1); // Pause de 4 secondes
            preparerNouvelleManche(joueurs, nbJoueurs, &paquet, compteur);
            compteur++;
    }
    
    // Fin de partie on affiche le gagnant et on demande aux joueurs si ils veulent enregistrer leur score 
    Enregistrejoueurs (joueurs, nbJoueurs);

    free(joueurs);
    free(paquet.cartes);
    return 0;
}
