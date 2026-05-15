#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "erreur.h"
#include "cartes.h"
#include "score.h"
#include "affichage.h"
#include "structure.h"


//Est-ce que l'utilisateur va piocher?
void Decision(int* decision,Perso* joueur){
	if(decision == NULL || joueur == NULL){
		exit(ERREUR_9);
	}
	int valide = 0;
     
	do{
		printf("\nVoulez-vous piocher ? \n- oui : 1 \n- non : 0\n -Voir les règles : 2\n");
		
        	//verification si scanf a bien marché, et si le nombre est respecté
        	if (scanf("%d", decision) == 1 && (*decision == 0 || *decision == 1 || *decision == 2)) {
            		valide = 1; //si c'est valide, c'est fini
        }else{
        	printf("\nErreur : saisie invalide.\n");
        	//On vide le tampon au cas où l'utilisateur aurais tapé un caractère
        	while (getchar() != '\n'); 
        	}
        
    	}while (valide == 0); //On recommence tant que ce n'est pas valide
  

}    
    
//nombre de joueurs dans la partie ?
void nmbJoueurs(int* nbJoueurs){
	if(nbJoueurs == NULL){
		exit(ERREUR_10);
	}
	int valide = 0;
	do{
		printf("Combien il y a t-il de joueurs dans la partie ?"EMOJI_JOUEUR"\n");
		if(scanf("%d",nbJoueurs) && (*nbJoueurs >= 3)){
			valide = 1;
			while(getchar() != '\n'); //On vide le tampon au cas où l'utilisateur aurais tapé un caractère
		}else{
			printf("\nErreur : saisie invalide.\n");
            while (getchar() != '\n'); //On vide le tampon au cas où l'utilisateur aurais tapé un caractère
		}
	} while (valide == 0);
}

bool Flip7(Perso joueur){
	int num = 0;
	for (unsigned int i = 0; i < joueur.nbcarte; i++) {
		// Seuls les cartes numéro compte pour le flip7
		if (joueur.carte[i].type == 'N') {
			num++;
		}
	}
	if (num == 7 && joueur.doublon == false) {
		return true;
	}else{
		return false;
	}
}

bool Doublon(Perso joueur){
	
	for (unsigned int i = 0; i < joueur.nbcarte; i++) {
		for (unsigned int j = 0; j < joueur.nbcarte; j++) {
			if (i == j) {
				continue; // On passe à la prochaine itération directement
			}
			if (joueur.carte[i].type == joueur.carte[j].type && (joueur.carte[i].numero == joueur.carte[j].numero)) {
				joueur.doublon = true;
			}
		}
	}
	return joueur.doublon;
}


bool MancheTerminee (Perso* joueurs, int nbJoueurs) {
	if(joueurs == NULL || nbJoueurs < 3 ){
		printf("\n Données invalide, erreur de programation ! \n");
		exit(ERREUR_11);
	}
	for(int i = 0; i < nbJoueurs; i++){
		if((joueurs+i)->Ajouer == false){
			return false;
		}
	}
	return true;
}

void preparerNouvelleManche (Perso* Joueurs, int nbJoueurs,Paquet* p, int compteur) {
	if (Joueurs == NULL || p == NULL) {
		exit(ERREUR_12);
	}
    for (int i = 0; i < nbJoueurs; i++) {
        Joueurs[i].Ajouer = false; // Tout le monde peut à nouveau jouer
        Joueurs[i].nbcarte = 0;    // On vide les mains
		Joueurs[i].doublon = false;
    }
	if (!FinDePartie(Joueurs, *p, nbJoueurs)) {
		creerPaquet(p,nbJoueurs);
		melanger(p);
    	printf(GRAS"\n---------------------------  C'est parti pour la manche %d  ---------------------------\n" RESET, compteur);
	}
}

void lancerManche(Perso* Joueurs, int nbJoueurs, Paquet *paquet) { //Joueurs => tous les joueurs de la partie
	if (Joueurs == NULL || paquet == NULL) {
		exit(ERREUR_13);

	}

	//On choisit qui commence (aléatoire)
	int joueurActuel = rand() % nbJoueurs, decision = 0, col = largeurTerminal();


	Carte c;
	bool flip_7 = false;


	printf("\n--- LE TOUR COMMENCE ---\n");
		
	//boucle du tour : tant que tout le monde n'a pas fini son tour
	while (!MancheTerminee(Joueurs, nbJoueurs) && !flip_7) {
			
    		// On ne fait jouer le joueur que s'il n'a pas encore joué
        	if (Joueurs[joueurActuel].Ajouer == false) {
				
				afficherSeparateur(col);
				afficherStatut(Joueurs, nbJoueurs);
				afficherSeparateur(col);

				afficherJoueur(Joueurs[joueurActuel].prenom);
				afficherNbcarte(paquet);
				
				//boucle de la pioche du joueur 
                Decision(&decision, &Joueurs[joueurActuel]);
       			if (decision == 1) {
        			Carte c = piocher(paquet);
					Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = c;
					Joueurs[joueurActuel].nbcarte++;
					
					printf("\nCarte piochée : ");
        			afficherCarteEsthetique(c);

					if (Joueurs[joueurActuel].nbcarte < MAIN) {
						printf("\n");
						printf("\nVoici ta main (%s) :  \n", Joueurs[joueurActuel].prenom);
						for(unsigned int i = 0; i < Joueurs[joueurActuel].nbcarte; i++){
								afficherCarteEsthetique(Joueurs[joueurActuel].carte[i]);
					}
					carteStop(Joueurs[joueurActuel], Joueurs, nbJoueurs, c);
					printf("\n");
					} else{
						printf("\nVotre main est pleine il n'est pas possible d'ajouter d'autres cartes ! \n");
					}

        			if (Doublon(Joueurs[joueurActuel])) {
        				printf("\nVous possédez déjà cette carte dans votre paquet... Vous êtes malheureusement éliminer de la manche\n");
                        Joueurs[joueurActuel].doublon = true;
            			Joueurs[joueurActuel].Ajouer = true;                        		

						//On ajoute la carte à la main du joueur
                        Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = c;
                        Joueurs[joueurActuel].nbcarte++;
                    }
            		if (Flip7(Joueurs[joueurActuel])) {
						printf("Bravo, %s a fait un flip 7 ! La manche est terminé et %s la gagne avec 15 points supplémentaires !\n",Joueurs[joueurActuel].prenom,Joueurs[joueurActuel].prenom);
						Joueurs[joueurActuel].score += 15;
						flip_7 = true;

            		}
				} else if( decision == 0) {
					printf(GRAS "\nC'est la fin de la manche pour toi !\n" RESET);
					Joueurs[joueurActuel].Ajouer = true;
			    } else{
					//afficheRegle();
				}    		
        	}
        	joueurActuel = (joueurActuel + 1) % nbJoueurs;
    	}
}

void InitialiseJoueurs(Perso* joueurs, int n){
	if(joueurs == NULL){
		exit(ERREUR_14);
	}
	for(int i = 0; i < n; i++) {
	        printf("\n--- Joueur %d ---\n", i + 1);
	        printf("Prenom : ");
			scanf("%s", joueurs[i].prenom);
	        
	        while(!PrenomValide(joueurs[i].prenom)){
	            printf("Saisie invalide, veuillez recommencer\n");
	            printf("Prenom : ");	
				scanf("%s", joueurs[i].prenom);
	        }

	        // initialisation du score, etc, à 0;
	        joueurs[i].score = 0;
	        joueurs[i].nbcarte = 0;
	        joueurs[i].Ajouer = false; 
			joueurs[i].doublon = false;

	}
}
