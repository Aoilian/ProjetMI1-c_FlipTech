#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "affichage.h"
#include "cartes.h"
#include "manche.h"
#include "score.h"



int main() {
    // On crée une nouvelle graine pour que les mélange ne soient pas les mêmes à chaque manche
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
    InitialiseJoueurs(joueurs, nbJoueurs);
    for(int i = 0; i < nbJoueurs; i++) {
        normaliserPrenom(joueurs[i].prenom);
    }

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
            
            preparerNouvelleManche(joueurs, nbJoueurs, &paquet, compteur);
            compteur++;
    }
    
    // Fin de partie on affiche le gagnant et on demande aux joueurs si ils veulent enregistrer leur score 
    Enregistrejoueurs (joueurs, nbJoueurs);

    free(joueurs);
    free(paquet.cartes);
    return 0;
}
