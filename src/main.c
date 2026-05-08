#include "structure.h"
#include "affichage.h"
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
    Perso* joueurs = NULL;
    int nbJoueurs = 0, nbpioche = 0, compteur = 2;
    
    effacerEcran();
    afficherTitrePrincipal();
    printf(RESET);

    
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
    while(!FinDePartie(joueurs, paquet,  nbJoueurs)){
            lancerManche(joueurs, nbJoueurs, &paquet, &nbpioche, doublon);
            for(int i = 0; i < nbJoueurs; i++){
                if(joueurs[i].nbcarte > 0){
                    CalculScore(&(joueurs[i]), joueurs[i].carte, joueurs[i].nbcarte, doublon[i]);
                }
                afficherTableauScores(&joueurs[i], joueurs, nbJoueurs);
            }
            majStats(&paquet, &statistiques);
            preparerNouvelleManche(joueurs, nbJoueurs, &paquet, compteur);
            compteur++;
    }
    
    // Fin de partie on affiche le gagnant et on demande aux joueurs si ils veulent enregistrer leur score 
    Enregistrejoueurs (joueurs, nbJoueurs);

    free(joueurs);
    return 0;
}
