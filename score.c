#include <stdbool.h>
#include <string.h>
#include "structure.h"
#include "manche.h"
#include "cartes.h"
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
			if(prenom[i] != '\0' && (prenom[i] > 64 && prenom[i] < 91)){
					prenom[i] -= 'A' - 'a'; 
			}
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

// Verifie que le joueur est valide
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

unsigned int AjouterBonus(unsigned int score, int bonus){
	if(score < 0 || ( bonus < 1 || bonus > 6)){
		exit(100);
	}

	//On applique les bonus au score du joueur
	switch (bonus) { 
	        case 1 :
					return score + 2;
			case 2 :
					return score + 4;
			case 3 :
					return score + 6;
			case 4 :
					return score + 8;
			case 5 :
					return score + 10;
			case 6 :
					return score * 2;
			default : 
					return score;
	}
	
}

// Calcule le score du joueur a la fin de son tour
void CalculScore(Perso* joueurs, Carte* main, int taille){
			if(joueurs == NULL || taille <= 0){
						exit(1000);
			}
			unsigned int somme = 0, b = 0;

			// Total de toutes las cartes numéro piochés
			for(int i = 0; i < taille; i++){
					if(main[i].type == 'N'){
							somme += (main+i)->numero;
					}
			}
			b = somme;

			// Ajout des cartes bonus après le tour 
			for(int j = 0; j < taille; j++){
					// On part du principe que le joueur voudra appliquer le *2 en dernier si il a plusieurs bonus
					if(main[j].type == 'B' && (main+j)->bonus != 1){
							b = AjouterBonus(b, (main+j)->bonus);
					}
			}

			// On applique le *2 à la fin 
			for(int k = 0; k < taille; k++){
					if(main[k].type == 'B' && (main+k)->bonus == 1){
							b = AjouterBonus(b, (main+k)->bonus);
					}
			}

			// Si le joueur a un doublon il ne marque aucun point
			if(!NoDoublon(main[taille-1], *joueurs)){
						b = 0;
			}
	
			joueurs->score += b;
}
					
void reinitialiserJoueur(Perso* joueurs, int nbjoueur){
		if(joueurs == NULL || nbjoueur < 3){
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
	    if(joueurs == NULL || nbjoueur < 3){
                printf("Erreur\n");
                exit(1);
            }

	    //On initialise le max et son adresse avec celle du premier joueur
	    unsigned int max = joueurs->score;
	    Perso* adresseMax;
	    adresseMax = joueurs;

	    //On fait une recherche de maximum sur le score pour renvoyer l'adresse et le score du gagnant
	    for(int j = 1; j < nbjoueur; j++){
			if(joueurs[j].score >  max){
				max = joueurs[j].score;
				adresseMax =  joueurs + j;
			} 
		}	
		printf("Le gagnant est : %s  avec un score de  %u   \n",adresseMax->prenom, max);
	 
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
			// On affiche le joueur et on indique qu'il a gagné la partie
			if((a + i) == designerGagnant(a, nbjoueur)){
						fprintf(fichier, "Prenom : %s | score : %u | vainqueur du flip7 \n", (a + i)->prenom, (a + i)->score); //On enregistre le nom du gagnant de la partie dans le fichier Fliptech.txt
			}
			fprintf(fichier, "Prenom : %s | score : %u \n", (a + i)->prenom, (a + i)->score);
		}
	}
}
