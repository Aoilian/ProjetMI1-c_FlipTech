#include <stdbool.h>
#include <string.h>
#include "manche.h"
#include "carte.h"
#include "score.h"

// Met la première lettre du prénom en majuscule
void Maj(char* prenom){
	if(prenom[0] != '\0' && (prenom[0] > 96 && prenom[0] < 123)){
		prenom[0] += 'A' - 'a' ; 
	}
}

// Met toutes les autres lettre du en minuscule
void Min(char* prenom){
	if(strlen(prenom) >= 2){
		for(int i = 1; i < strlen(prenom); i++){
					prenom[i] -= 'A' - 'a'; 
		}
	}
}

// Verifie la validité du prénom du joueur
bool PrenomValide(char* prenom){
	for(int i = 0; i < strlen(prenom); i++){
				if(prenom[i] >  122 || prenom[i] < 65 || (prenom[i] > 90 && prenom[i] < 97)){
					return false;
				}
	}
	return true;
}

//On verifie que le joueur est valide
int PersoValide(Perso a){
		for(int i = 0; i < 7; i++ ){
				if(a.carte[i].type == 'N' && (a.carte[i].numero < 0 || a.carte[i].numero > 12)){
					return -1;
				}
				else if(a.carte[i].type == 'B' && (a.carte[i].numero < 0 || a.carte[i].numero > 6)){
					return -1;
				}
		}
		if(a.nbcarte < 0 || a.nbcarte > 7){
				return -1;
		}
		else if(PrenomValide(a.prenom) == false){
				return -1;
		}
		return 0;
}

unsigned int CalculScore(Perso joueur, Carte carte){
			if(PersoValide(a) == -1){
						exit(1000);
			}
			if(carte.type == 'N'){
						perso.score += carte.numero;
			}
}
					
unsigned int AjouterBonus(Perso a, int bonus){
	if(PersoValide(a) == -1){
		exit(100);
	}

	//On applique les bonus au score du joueur
	switch (bonus) { 
	        case 1 :
					return a.score * 2;
			case 2 :
					return a.score + 2;
			case 3 :
					return a.score + 4;
			case 4 :
					return a.score + 6;
			case 5 :
					return a.score + 8;
			case 6 :
					return a.score + 10;
			default : 
					return a.score;
	}
	
}

void reinitialiserJoueur(Perso* joueurs, int nbjoueur){
		if(joueurs == NULL || nbjoueur < 2){
                	printf("Erreur\n");
                	exit(1);
		}
		for(int i = 0; i < nbjoueur; i++){
			//On remet à 0 le nombre de carte que les joueurs possèdent quand la manche est terminé
			(joueurs+i)->nbcarte = 0;
			for(int j = 0; j < 7; j++){
				//On supprime la main des joueurs quand la manche est terminé
				(joueurs + i)->carte[j].numero = 0;
				(joueurs + i)->carte[j].bonus = 0;
				(joueurs + i)->carte[j].type = '\0';
			}
		}
}

bool FinDePartie(Perso* joueurs, Paquet pioche, int nbjoueur){
	if(joueurs == NULL || nbjoueur == 0 || pioche.nbCartes < 0){
		printf("Erreur \n");
		exit(160);
 	}

	for(int i = 0; i < nbjoueur; i++){
		//La partie prend fin si un des joueurs atteint ou dépasse le seuil de 200 point ou que la pioche est vide 
		if((joueurs+i)->score >= 200 ||  pioche.nbCartes == 0){
			return true;
		}
	}
	return false;
}

Perso* designerGagnant(Perso* joueurs, int nbjoueur){
	    if(joueurs == NULL || nbjoueur < 2){
                printf("Erreur\n");
                exit(1);
        }

	    //On initialise le max et son adresse avec celle du premier joueur
	    unsigned int max = joueurs->score;
	    Perso* adresseMax; 
		Perso* adresseMax2;
		adresseMax = joueurs;
		adresseMax2 = NULL;

	    //On fait une recherche de maximum sur le score pour renvoyer l'adresse et le score du gagnant
	    for(int j = 1; j < nbjoueur; j++){
			if(joueurs[j].score >  max){
				max = joueurs[j].score;
				adresseMax =  joueurs + j;
				adresseMax2 = NULL;
			} 
			else if(joueurs[j].score == max){ //Cas ou Deux joueurs ont le même score a la fin de la partie
				   max = (joueurs + j)->score;
				   adresseMax2 = joueurs + j;
			}
	     }

		 if(adresseMax2 != NULL){
			printf("Les gagnant sont : %s et %s  avec un score de  %u   \n",adresseMax->prenom, adresseMax2->prenom, max);
		 }
		 else{
			printf("Le gagnant est : %s  avec un score de  %u   \n",adresseMax->prenom, max);
		 }
	     
		 //On retourne l'adresse du joueur qui a gagné
		 return adresseMax;
}

//On enregistre le Nom de chaque gagnant de la partie
void Enregistrejoueurs(Perso* a, int nbjoueur){
	if(a == NULL || nbjoueur < 2){
            printf("Erreur\n");
            exit(5);
    }

	//On ouvre le fichier Fliptech.txt
	FILE* fichier = NULL; 
	fichier = fopen("Fliptech.txt", "w+"); 

	for(int i = 0; i < nbjoueur; i++){
		char choix;

		printf("%s veux tu enregistrer ton score sur le fichier Fliptech ? \n", (a + i)->prenom);
		while(scanf("%c",&choix) != 1 && (choix != 'O' && choix != 'N')){ //Tant que l'utilisateur ne saisi pas 'O4 OU 'N' on lui redemande de saisir
					printf("Saisi invalide, veuillre réessayer. \n");
					while(getchar() != '\n'); //On vide le tampon après la saisi de l'utilisateur
		}
		if(choix == 'O'){
			//
			if((a + i) == designerGagnant(a, nbjoueur)){
						fprintf(fichier, "Prenom : %s | score : %u | vainqueur \n", (a + i)->prenom, (a + i)->score); //On enregistre le nom du gagnant de la partie dans le fichier Fliptech.txt
			}
			fprintf(fichier, "Prenom : %s | score : %u \n", (a + i)->prenom, (a + i)->score);
		}
	}
}

