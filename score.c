#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
	unsigned int carte[7];
	unsigned int score;
	unsigned int nbcarte;
	char prenom[255];
}Perso;

//Verifier que le joueur est valide
int PersoValide(Perso a){
		for(int i = 0; i < 7; i++ ){
				if(a.carte[i] < 0 || a.carte[i] > 12){
					return -1;
				}
		}
		if(a.nbcarte < 0 || a.nbcarte > 7){
			return -1;
		}
		return 0;
}

unsigned int calculScoreMancheTot(Perso a, int bonus){
	//On applique les bonus au score du joueur
	switch (bonus) { 
	        case -1 :
			return a.score * 2;
			default : 
					return a.score;
	}
	
}

void reinitialiserJoueur(Perso* joueurs, int taille){
		if(joueurs == NULL || taille < 2){
                	printf("Erreur\n");
                	exit(1);
                }
		for(int i = 0; i < taille; i++){
			for(int j = 0; j < 7; j++){
				joueurs->carte[j] = 0;
			}
		}
}

bool FinDePartie(Perso* joueurs, unsigned int* pioche, int taille){
	if(joueurs == NULL || pioche == NULL){
		printf("Erreur\n");
		exit(1);
 	}
	for(int i = 0; i < taille; i++){
		//La partie prend fin si un des joueurs atteint ou dépasse le seuil de 200 point ou que la pioche est vide 
		if(calculScoreMancheTot(joueurs[i], -1) >= 200 ||  pioche == 0){
			return true;
		}
	}
	return false;
}

void designerGagnant(Perso* joueurs, int taille){
	    if(joueurs == NULL || taille < 2){
                printf("Erreur\n");
                exit(1);
        }
		int bonus = 0;
	    //On initialise le max avec la valeur du premier joueur 
	    unsigned int max = calculScoreMancheTot(joueurs[0],bonus);
	    Perso* adresseMax; 
	    //On fait une recherche de maximum sur le score pour renvoyer l'adresse et le score du gagnant
	    for(int j = 1; j < taille; j++){
			if(calculScoreMancheTot(joueurs[j],bonus) >  max){
				max = calculScoreMancheTot(joueurs[j],-1);
				adresseMax =  joueurs + j;
			} 
			//Faire le cas ou 2 Joueurs ont le même score final
	     }
	     printf("Le gagnant est : %s  avec un score de  %u   \n",adresseMax->prenom, max);
}

//On enregistre le Nom de chaque gagnant de la partie
void savejoueur(Perso* a, int nbjoueur){
	if(a == NULL){
            printf("Erreur\n");
            exit(5);
    }
	FILE* fichier = NULL;
	fichier = fopen("Fliptech.txt", "w+");
	for(int i = 0; i < nbjoueur; i++){
		char choix;
		unsigned int score = calculScoreMancheTot(a[9], -1); // A MODIFIER
		while(scanf("%c",&choix) != 1 && choix != 'O' && choix != 'N'){ //MARCHE PAS
					printf("Saisi invalide, veuillre réessayer. \n");
					while(getchar() != '\n'); //On vide le buffer après la saisi de l'utilisateur
		}
		if(choix == 'O'){
			fprintf(fichier, "Prenom : %s | score : %u \n", a->prenom, score); //A MODIFIER
		}
		//Faire le cas ou le joueur dis oui et il a gagné 
	}
}

