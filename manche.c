#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cartes.h"
#include "score.h"
//#include "score.h"


//Est-ce que l'utilisateur va piocher?
void Decision(int* decision,Perso* joueurs){
	if(decision == NULL || joueurs == NULL){
		exit(10);
	}
	int valide = 0;
     
	do{
		printf("Voulez-vous piocher ? \n- oui : 1 \n- non : 0\n");
		
        	//verification si scanf a bien marché, et si le nombre est respecté
        	if (scanf("%d", decision) == 1 && (*decision == 0 || *decision == 1)) {
            		valide = 1; //si c'est valide, c'est fini
        }else{
        	printf("Erreur : saisie invalide.\n");
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
		printf("Combien y a t-il de joueurs dans la partie ?\n");
		if(scanf("%d",nbJoueurs) && (*nbJoueurs >= 3 && *nbJoueurs <= 18)){
			valide = 1;
		}else{
		printf("Erreur : saisie invalide.\n");
           	//On vide le tampon au cas où l'utilisateur aurais tapé un caractère
            	while (getchar() != '\n'); 
		}
	}while(valide == 0);
}

bool Flip7(Perso joueur){
	int num = 0;
	for(int i = 0; i<joueur.nbcarte; i++){
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
	for(int i = 0; i<joueur.nbcarte; i++){
		if(joueur.carte[i].numero == carte.numero && joueur.carte[i].bonus == carte.bonus){
			nodoublon = false;
		}
	
	}
	return nodoublon;
}

void preparerNouvelleManche(Perso* Joueurs, int nbJoueurs,Paquet* p) {
	if(Joueurs == NULL || p == NULL){
		exit(14);
	}
    for (int i = 0; i < nbJoueurs; i++) {
        Joueurs[i].Ajouer = false; // Tout le monde peut à nouveau jouer
        Joueurs[i].nbcarte = 0;    // On vide les mains
    }
    //on creer le nouveau paquet
    creerPaquet(p);
    melanger(p);
    printf("Le paquet a été reformé et mélanger. C'est parti pour la nouvelle manche !");
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

void lancerManche(Perso* Joueurs, int nbJoueurs, Paquet *paquet, int* nbpioche){ //Joueurs => tous les joueurs de la partie
	if(Joueurs == NULL || paquet == NULL || (nbJoueurs < 3 || nbJoueurs >18)){
		exit(16);
	}
	//On choisit qui commence (aléatoire)
	int joueurActuel = rand() % nbJoueurs;

	int decision;
	Carte c;
	bool doublon, gagne;



	printf("\n--- LE TOUR COMMENCE ---\n");
	printf("Le hasard a choisi : %s commence !\n", Joueurs[joueurActuel].prenom);

	//boucle du tour : tant que tout le monde n'a pas fini son tour
	while (!MancheTerminee(Joueurs, nbJoueurs)){
        
        	// On ne fait jouer le joueur que s'il n'a pas encore joué
        	if (Joueurs[joueurActuel].Ajouer == false) {
				Decision(&decision, &Joueurs[joueurActuel]);//initialisation à 1 pour rentrer dans la boucle
        		doublon = false;
        		gagne = false;
        	}
        		//boucle de la pioche du joueur 
        	while(decision == 1 && !doublon && !gagne){
                    	Decision(&decision, &Joueurs[joueurActuel]);
       			if(decision == 1){
					c = piocher(paquet);
        			afficherCarte(c);
        			nbpioche ++;
					if(!NoDoublon(c,Joueurs[joueurActuel])){
        			printf("Vous possédez déjà cette carte dans votre paquet... Vous êtes malheureusement éliminer de la manche \n\n");
        			Joueurs[joueurActuel].nbcarte = 0; // Il perd ses cartes
                        	doublon = true;
        			}
					else{
        			//On ajoute la carte à la main du joueur
                        	Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = c;
                        	Joueurs[joueurActuel].nbcarte++;
                    }
        		
            				
            		if(Flip7(Joueurs[joueurActuel])){
            					printf("Bravo, %s a fait un flip 7 ! La manche est terminé et %s la gagne avec 15 points supplémentaires !\n",Joueurs[joueurActuel].prenom,Joueurs[joueurActuel].prenom);
            					gagne = true;
            		}      			
        		}
        			                 		
        		//Une fois qu'il a fini, on marque qu'il a joué
        		Joueurs[joueurActuel].Ajouer = true;
        		if(gagne){
        			break;
        		}
        	}

        	//on passe au joueur suivant
        	joueurActuel = (joueurActuel + 1) % nbJoueurs;
        	printf("C'est à %s de jouer !\n",Joueurs[joueurActuel].prenom);
    	}
	
}


void enregistrerJoueurs(Perso* joueurs, int n){
	if(joueurs == NULL){
		exit(17);
	}
	for(int i = 0; i < n; i++) {
	        printf("\n--- Joueur %d ---\n", i + 1);
	        printf("Nom : ");
			scanf("%s", joueurs[i].prenom);
	        
	        while(!PrenomValide(joueurs[i].prenom)){
	            printf("saisie invalide\n");
	            printf("Nom : ");
				scanf("%s", joueurs[i].prenom);
	        }

	        // initialisation du score, etc, à 0;
	        joueurs[i].score = 0;
	        joueurs[i].nbcarte = 0;
	        joueurs[i].Ajouer = false; // ou 0 ??
	}
}
/*
int main(){
	int piocher;
	int nbJoueur;
	decision(&piocher);
	nmbJoueurs(&nbJoueur);
	return 0;
}

Pour le main : 
while(partie_en_cours) {
    while(tour_en_cours) {
        // Appelle ta fonction decision()
        // Si piocher == 1 -> tire une carte -> verifie doublon
        // Si doublon -> tour_en_cours = 0 et score_tour = 0
        // Si piocher == 0 -> ajoute score_tour au score_total et tour_en_cours = 0
    }
}
*/
