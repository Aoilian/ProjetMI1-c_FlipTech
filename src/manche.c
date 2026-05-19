#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "erreur.h"
#include "cartes.h"
#include "score.h"
#include "affichage.h"
#include "structure.h"

// Met la première lettre du prénom en majuscule
void Maj (char* prenom) {
	if(prenom[0] != '\0' && ((prenom[0] >= 'a' && prenom[0] <= 'z') || ((unsigned int)prenom[0] >= 0xDF && (unsigned int)prenom[0] <= 0xFF))) {
		prenom[0] += 'A' - 'a' ; 
	}
}

// Met toutes les autres lettre du en minuscule
void Min (char* prenom) {
	if(strlen(prenom) >= 2){
		for(unsigned int i = 1; i < strlen(prenom); i++){
			if(prenom[i] != '\0' && ((prenom[i] >= 'A' && prenom[i] <= 'Z') || ((unsigned int)prenom[i] >= 0xC0 && (unsigned int)prenom[i] <= 0xDE))) {
					prenom[i] -= 'A' - 'a'; 
			}
		}
	}
}

void normaliserPrenom (char* prenom) {
	Maj(prenom);
	Min(prenom);
}

//Est-ce que l'utilisateur va piocher?
void Decision(int* decision,Perso* joueur){
	if(decision == NULL || joueur == NULL){
		exit(ERREUR_9);
	}
	int valide = 0;
     
	do{
		printf("\nVoulez-vous piocher ? \n- oui : 1 \n- non : 0\n");
		
        	//verification si scanf a bien marché, et si le nombre est respecté
        	if (scanf("%d", decision) == 1 && (*decision == 0 || *decision == 1 || *decision == 2)) {
            		valide = 1; //si c'est valide, c'est fini
        }else{
        	printf("\nErreur : Saisie invalide.\n");
        	//On vide le tampon au cas où l'utilisateur aurais tapé un caractère
        	while (getchar() != '\n'); 
        	}
        
    	}while (valide == 0); //On recommence tant que ce n'est pas valide
}    


void AfficherRegle(){
	printf(GRAS V_BLANC"\n\nRègles du jeu : FlipTech ou --flip7--\n\n");
	printf("Le Flip7 est un jeu de cartes mêlant hasard, statistiques et prise de risque. Il peut être joué à autant de joueurs que l’on souhaite (3 joueurs minimum).\n");
	printf("\nObjectif du jeu\nAccumuler le plus de points possible au fil des manches.\n");
	printf("Les cartes numéros rapportent leur valeur, et les cartes bonus modifient le score final (multiplication ou ajout)\n");
	printf("\nComposition du jeu\nLe jeu contient 85 cartes (ou plus selon le nombre de joueurs) :\n");
	printf("- 79 cartes numéros allant de 0 à 12, avec une quantité croissante selon le numéro (ex : 1 carte “0”, 12 cartes “12”)\n");
	printf("- 6 cartes bonus : x2, +2, +4, +6, +8, +10\n");
	printf("- Une carte spéciale : STOP, qui permet de stopper un autre joueur de la partie quand on la pioche\n");
	printf("\nDéroulement d’une manche\n");
	printf("Les joueurs jouent dans le même ordre, chacun leur tour.\n");
	printf("À son tour, un joueur peut :\n1) S'arrêter : Il conserve les points déjà accumulés dans la manche\n2) Piocher une carte (4 situations possibles) :\n");
	printf("Nouvelle carte numéro →  Elle s’ajoute à sa collection et augmente son score de manche.\nCarte bonus → Son effet s’appliquera au score final de la manche.\n");
	printf("Carte numéro déjà obtenue → Le joueur perd la manche et marque 0 point.\n7 cartes différentes obtenues → La manche s’arrête immédiatement pour tout le monde + Le joueur gagne +15 points bonus pour avoir fait un flip7.\n");
	printf("\nFin de manche\nUne manche se termine lorsque :\nun joueur obtient 7 cartes différentes,ou tous les joueurs se sont arrêtés,ou tous les joueurs restants ont perdu en tirant un doublon\n");
	printf("\nFin de partie\nLa partie s’arrête si : un joueur atteint 200 points ou plus\nLe joueur avec le score total le plus élevé remporte la partie.\n\n");
}

void VoirRegle(){
	int lire = 0, valide = 0;
	do {
		printf("Voulez-vous consulter les rêgles du jeu avant de commencer la partie ?\n- Oui : 1 \n- Non : 0\n");
		if (scanf("%d", &lire) == 1 && (lire == 0 || lire == 1)) {
            		valide = 1; //si c'est valide, c'est fini
        } else {
        	printf("\nErreur : Saisie invalide.\n");
        	//On vide le tampon au cas où l'utilisateur aurais tapé un caractère
        	while (getchar() != '\n'); 
        }
	} while(valide == 0);
	if (lire == 1) {
		effacerEcran();
		AfficherRegle();
	}
}
    
//nombre de joueurs dans la partie ?
void nmbJoueurs(int* nbJoueurs){
	if(nbJoueurs == NULL){
		exit(ERREUR_10);
	}
	int valide = 0;
	do{
		printf(RESET V_BLANC"\nCommençons, combien il y a t-il de joueurs dans la partie ?"EMOJI_JOUEUR"\n");
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
			if(joueur.carte[i].type == 'N'){
				if (joueur.carte[i].type == joueur.carte[j].type && (joueur.carte[i].numero == joueur.carte[j].numero)) {
					joueur.doublon = true;
				} else{
					continue; // Si on tombe sur une carte bonus ou speciale on passe à la prochaine itération car seules les cartes numéros comptent comme des doublons
				}
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

void preparerNouvelleManche (Perso* Joueurs, int nbJoueurs,Paquet* paquet, int compteur) {
	if (Joueurs == NULL || paquet == NULL) {
		exit(ERREUR_12);
	}
    for (int i = 0; i < nbJoueurs; i++) {
        Joueurs[i].Ajouer = false; // Tout le monde peut à nouveau jouer
		Joueurs[i].doublon = false;
    }
	VideLaMain(Joueurs, nbJoueurs);
	if (!FinDePartie(Joueurs, *paquet, nbJoueurs) && paquet->nbCartes > 0) {
    	printf(GRAS"\n---------------------------  C'est parti pour la manche %d  ---------------------------\n" RESET, compteur);
	}
}

void lancerManche(Perso* Joueurs, int nbJoueurs, Paquet *paquet) { //Joueurs => tous les joueurs de la partie
	if (Joueurs == NULL || paquet == NULL) {
		exit(ERREUR_13);

	}

	// On choisit qui commence (aléatoire)
	int joueurActuel = rand() % nbJoueurs;
	int decision = 0;
	// Variable colonne qui stocke la largeur du terminale
	int col = largeurTerminal();

	bool flip_7 = false;


	printf("\n--- LE TOUR COMMENCE ---\n");
		
	//boucle du tour : tant que tout le monde n'a pas fini son tour
	while (!MancheTerminee(Joueurs, nbJoueurs) && !flip_7 && paquet->nbCartes > 0) {
			
    		// On ne fait jouer le joueur que s'il n'a pas encore joué
        	if (Joueurs[joueurActuel].Ajouer == false) {
				
				afficherSeparateur(col);
				afficherStatut(Joueurs, nbJoueurs);
				afficherSeparateur(col);

				afficherJoueur(Joueurs[joueurActuel].prenom);
				if (Joueurs[joueurActuel].nbcarte > 0 && Joueurs[joueurActuel].nbcarte < MAIN) {
					printf("\n");
					printf("\nVoici ta main (%s) :  \n", Joueurs[joueurActuel].prenom);
					for(unsigned int i = 0; i < Joueurs[joueurActuel].nbcarte; i++){
							afficherCarteEsthetique(Joueurs[joueurActuel].carte[i]);
					}
				}
				afficherNbcarte(paquet);
				if (Joueurs[joueurActuel].nbcarte >= MAIN) {
						printf("\nVotre main est pleine, vous ne pouvez plus jouer");
						Joueurs[joueurActuel].Ajouer = true;
				} else{
				//boucle de la pioche du joueur 
					Decision(&decision, &Joueurs[joueurActuel]);
					if (decision == 1) {
							Carte c = piocher(paquet);
							Joueurs[joueurActuel].carte[Joueurs[joueurActuel].nbcarte] = c;
							Joueurs[joueurActuel].nbcarte++;
							
							printf("\nCarte piochée : ");
							afficherCarteEsthetique(c);

							carteStop(Joueurs[joueurActuel], Joueurs, nbJoueurs, c);
							printf("\n");
							

							if (Doublon(Joueurs[joueurActuel])) {
								printf("\nVous possédez déjà cette carte dans votre paquet... Vous êtes malheureusement éliminer de la manche\n");
								Joueurs[joueurActuel].doublon = true;
								Joueurs[joueurActuel].Ajouer = true;                        		
							}
							if (Flip7(Joueurs[joueurActuel])) {
								printf("Bravo, %s a fait un flip 7 ! La manche est terminé et %s la gagne avec 15 points supplémentaires !\n",Joueurs[joueurActuel].prenom,Joueurs[joueurActuel].prenom);
								Joueurs[joueurActuel].score += 15;
								flip_7 = true;

							}
						} else {
						printf(GRAS "\nC'est la fin de la manche pour toi !\n" RESET);
						Joueurs[joueurActuel].Ajouer = true;    		
					}
				}
			}	
		joueurActuel = (joueurActuel + 1) % nbJoueurs;
		
		if (paquet->nbCartes == 0) {
        	printf("\nIl n'y a plus de cartes dans le paquet, la partie prend fin !\n");
		}
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
	        
	        while(!PrenomValide(joueurs[i].prenom) ){
	            printf("Saisie invalide, veuillez recommencer\n");
	            printf("Prenom (20 caractères max): ");	
				scanf("%s", joueurs[i].prenom);
	        }

	        // initialisation du score, etc, à 0;
	        joueurs[i].score = 0;
	        joueurs[i].nbcarte = 0;
	        joueurs[i].Ajouer = false; 
			joueurs[i].doublon = false;
	}
}