#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cartes.h"
#include "score.h"
#include "affichage.h"
#include "structure.h"


//Est-ce que l'utilisateur va piocher?
void Decision(int* decision,Perso* joueur){
	if(decision == NULL || joueur == NULL){
		exit(10);
	}
	int valide = 0;
     
	do{
		printf("\nVoulez-vous piocher ? \n- oui : 1 \n- non : 0\n");
		
        	//verification si scanf a bien marché, et si le nombre est respecté
        	if (scanf("%d", decision) == 1 && (*decision == 0 || *decision == 1)) {
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
		exit(12);
	}
	int valide = 0;
	do{
		printf("Combien il y a t-il de joueurs dans la partie ?"EMOJI_JOUEUR"\n");
		if(scanf("%d",nbJoueurs) && (*nbJoueurs >= 3 && *nbJoueurs <= 18)){
			valide = 1;
			while(getchar() != '\n'); //On vide le tampon au cas où l'utilisateur aurais tapé un caractère
		}else{
			printf("\nErreur : saisie invalide.\n");
            while (getchar() != '\n'); //On vide le tampon au cas où l'utilisateur aurais tapé un caractère
		}
	}while(valide == 0);
}

bool Flip7(Perso joueur){
	int num = 0;
	for(unsigned int i = 0; i < joueur.nbcarte; i++){
		if(joueur.carte[i].type == 'N'){
			num++;
		}
	}
	if(num == 7){
		return true;
	}else{
		return false;
	}
}

bool NoDoublon(Carte carte, Perso joueur){
	int nodoublon = true;
	for(unsigned int i = 0; i < joueur.nbcarte; i++){
		if(joueur.carte[i].type == 'N' && (joueur.carte[i].numero == carte.numero)){
			nodoublon = false;
		}
	
	}
	return nodoublon;
}


bool MancheTerminee(Perso* joueurs, int nbJoueurs){
	if(joueurs == NULL || (nbJoueurs < 3 || nbJoueurs >18)){
		exit(15);
	}
	for(int i = 0; i < nbJoueurs; i++){
		if((joueurs+i)->Ajouer == false){
			return false;
		}
	}
	return true;
}

void preparerNouvelleManche(Perso* Joueurs, int nbJoueurs,Paquet* p, int compteur) {
	if(Joueurs == NULL || p == NULL){
		exit(14);
	}
    for (int i = 0; i < nbJoueurs; i++) {
        Joueurs[i].Ajouer = false; // Tout le monde peut à nouveau jouer
        Joueurs[i].nbcarte = 0;    // On vide les mains
    }
	if(!FinDePartie(Joueurs, *p, nbJoueurs)){
		creerPaquet(p);
		melanger(p);
    	printf("\n---------------------------  C'est parti pour la manche %d  ---------------------------\n", compteur);
	}
}

void lancerManche(Perso* Joueurs, int nbJoueurs, Paquet *paquet, int* nbpioche, bool* doublon, Stats statistiques){ //Joueurs => tous les joueurs de la partie
	if(Joueurs == NULL || paquet == NULL || (nbJoueurs < 3 || nbJoueurs >18)){
		exit(16);
	}
	//On choisit qui commence (aléatoire)
	int joueurActuel = rand() % nbJoueurs;

	int decision = 0;
	Carte c;
	bool gagne;

	

	// On initialise le tableau de doublon à "faux" pour tous les joueurs au début de la manche
	for(int i = 0; i < nbJoueurs; i++){
		doublon[i] = false;
	}



	printf("\n--- LE TOUR COMMENCE ---\n");
	printf("Le hasard a choisi : %s commence !\n", Joueurs[joueurActuel].prenom);

	//boucle du tour : tant que tout le monde n'a pas fini son tour
	while (!MancheTerminee(Joueurs, nbJoueurs)){
			 afficherPaquet(paquet);

        	// On ne fait jouer le joueur que s'il n'a pas encore joué
        	if (Joueurs[joueurActuel].Ajouer == false) {
        		doublon[joueurActuel] = false;
        		gagne = false;
				Decision(&decision, &Joueurs[joueurActuel]); // on demande au joueur s'il veut piocher ou pas
        	}
			

        	//boucle de la pioche du joueur 
        	while(decision == 1 && !(doublon[joueurActuel]) && !gagne){
       			if(decision == 1){
					printf("\nCarte piochée : ");
					c = piocher(paquet);
        			afficherCarteEsthetique(c);
					printf("\n");

        			(*nbpioche)++;
					majStats(c, &statistiques);
            		
					if(!NoDoublon(c,Joueurs[joueurActuel])){
        					printf("Vous possédez déjà cette carte dans votre paquet... Vous êtes malheureusement éliminer de la manche \n\n");
                        	doublon[joueurActuel] = true;
        			}
					else{
        			//On ajoute la carte à la main du joueur
                        	Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = c;
                        	Joueurs[joueurActuel].nbcarte++;
							doublon[joueurActuel] = false;
							printf("\nVoici ta main (%s) :  \n", Joueurs[joueurActuel].prenom);
							for(unsigned int i = 0; i < Joueurs[joueurActuel].nbcarte; i++){
									afficherCarteEsthetique(Joueurs[joueurActuel].carte[i]);
							}
							printf("\n");
					}
        		
            				
            		if(Flip7(Joueurs[joueurActuel])){
            					printf("\nBravo, %s a fait un flip 7 ! La manche est terminé et %s la gagne avec 15 points supplémentaires !\n",Joueurs[joueurActuel].prenom,Joueurs[joueurActuel].prenom);
            					gagne = true;
            		}      			
        		}
				if(!gagne && !(doublon[joueurActuel])){
					afficherStat(statistiques);
					Decision(&decision, &Joueurs[joueurActuel]); // on redemande au joueur s'il veut piocher ou pas
				}
        			                 		
        		if(gagne){
        			decision = 0; // pour sortir de la boucle de pioche
					Joueurs[joueurActuel].score += 15; // on ajoute les points du flip7
        		}
        	}
			//Une fois qu'il a fini, on marque qu'il a joué
        	Joueurs[joueurActuel].Ajouer = true;

        	//on passe au joueur suivant à condition que la manche ne soit pas terminer
			if(!MancheTerminee(Joueurs,nbJoueurs)){
				joueurActuel = (joueurActuel + 1) % nbJoueurs;
				printf("\nC'est à %s de jouer !\n",Joueurs[joueurActuel].prenom);
			}
			
    	}
	
}


void enregistrerJoueurs(Perso* joueurs, int n){
	if(joueurs == NULL){
		exit(17);
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
	        joueurs[i].Ajouer = false; // ou 0 ??
	}
}