#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "affichage.h"
#include "cartes.h"
#include "structure.h"
#include "score.h"
#include "erreur.h"

// Verifie la validité du prénom du joueur
bool PrenomValide (char* prenom) {
	if (prenom == NULL || prenom[0] == '\0') {
		return false;
	}

	for (unsigned int i = 0; i < strlen(prenom); i++) {
        // Sauter les octets de continuation UTF-8 (ex: 2e octet de 'é')
        if ((unsigned char)prenom[i] >= 0x80 && (unsigned char)prenom[i] < 0xC0) {
            continue;
        }
        // Sauter l'octet de tête multi-octet (ex: 1er octet de 'é')
        if ((unsigned char)prenom[i] >= 0xC0 && (unsigned char)prenom[i] != 0xF7) {
            continue;
        }
        // Si c'est un caractère ASCII, on accepte seulement les lettres
        if ((prenom[i] < 'A' || prenom[i] > 'Z') && (prenom[i] < 'a' || prenom[i] > 'z')) {
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
				else if(a.carte[i].type == 'B' && (a.carte[i].bonus < PLUS2|| a.carte[i].bonus > FOIS2)){
					return -1;
				}
		}
		if(a.nbcarte > 7){
				return -1;
		}
		else if(PrenomValide(a.prenom) == false){
				return -1;
		}
		return 0;
}

unsigned int AjouterBonus(unsigned int score, int bonus){
	if(bonus < 1 || bonus > 6){
		exit(ERREUR_1);
	}

	//On applique les bonus au score du joueur
	switch (bonus) { 
	        case PLUS2 :
					return score + 2;
			case PLUS4 :
					return score + 4;
			case PLUS6 :
					return score + 6;
			case PLUS8 :
					return score + 8;
			case PLUS10 :
					return score + 10;
			case FOIS2 :
					return score * 2;
	}
	return score;
}

// Calcule le score du joueur a la fin de son tour
void CalculScore(Perso* joueurs, Carte* main, int taille,bool doublon){
			if(joueurs == NULL || main == NULL || taille <= 0){
						return;
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
					if(main[j].type == 'B' && (main+j)->bonus != FOIS2){
							b = AjouterBonus(b, (main+j)->bonus);
					}
			}

			// On applique le *2 à la fin 
			for(int k = 0; k < taille; k++){
					if(main[k].type == 'B' && (main+k)->bonus == FOIS2){
							b = AjouterBonus(b, (main+k)->bonus);
					}
			}
			if(doublon){
				b = 0;
			}
			joueurs->score += b;
}
			
					
void VideLaMain(Perso* joueurs, int nbjoueur){
		if(joueurs == NULL || nbjoueur < 3){
                	printf("\nErreur\n");
                	exit(ERREUR_2);
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
	if(joueurs == NULL || nbjoueur < 3){
		printf("\nErreur \n");
		exit(ERREUR_3);
 	}

	for(int i = 0; i < nbjoueur; i++){
		//La partie prend fin si un des joueurs atteint ou dépasse le seuil de 200 point ou que la pioche est vide 
		if((joueurs+i)->score >= 200 || pioche.nbCartes == 0){
			return true;
		}
	}
	return false;
}

Perso* designerGagnant(Perso* joueurs, int nbjoueur){
	    if(joueurs == NULL || nbjoueur < 3){
                printf("\nErreur\n");
                exit(ERREUR_4);
            }

	    // On initialise le max et son adresse avec celle du premier joueur
	    unsigned int max = joueurs->score;
	    Perso* adresseMax;
	    adresseMax = joueurs;

	    // On fait une recherche de maximum sur le score pour renvoyer l'adresse et le score du gagnant
	    for(int j = 1; j < nbjoueur; j++){
			if(joueurs[j].score >  max){
				adresseMax =  &joueurs[j];
				max = joueurs[j].score;
			} 
		}	
		afficherGagnant(adresseMax->prenom);
	 
		//On retourne l'adresse du joueur qui a gagné
		return adresseMax;
}

//On enregistre le Nom de chaque gagnant de la partie
void Enregistrejoueurs(Perso* a, int nbjoueur){
	if(a == NULL || nbjoueur < 3){
            printf("\nErreur\n");
            exit(ERREUR_5);
    }
	Perso* gagnant = designerGagnant(a, nbjoueur);
	char nomFichier[255];

	printf("\nQuel nom donnez vous au fichier ?\n ");
	while(scanf("%254s", nomFichier) != 1){
		printf("Saisie invalide, veuillez recommmencer");
		while(getchar() != '\n'); // On vide le tampon
	}

	//On ouvre le fichier Fliptech.txt
	FILE* fichier = NULL; 
	fichier = fopen(nomFichier, "w+"); 

	if(fichier == NULL){
		printf("\nErreur le fichier %s n'a pas pu être créer", nomFichier);
		return;
	}

	for(int i = 0; i < nbjoueur; i++){
		char choix;


		printf(RESET"\n%s veux tu enregistrer ton score sur le fichier %s ? (oui : O / non : N) \n", (a + i)->prenom, nomFichier);
		while(scanf(" %c",&choix) != 1 || (choix != 'O' && choix != 'N')){ //Tant que l'utilisateur ne saisi pas 'O4 OU 'N' on lui redemande de saisir
					printf("Saisi invalide, veuillre réessayer. \n");
					while(getchar() != '\n'); //On vide le tampon après la saisi de l'utilisateur
		}
		if(choix == 'O'){
			// On affiche le joueur et on indique qu'il est vainqeur du flip tech si il a gagné une partie
			if((a + i) == gagnant){
						fprintf(fichier, "Prenom : %s | score : %u | vainqueur du flip tech \n", (a + i)->prenom, (a + i)->score); //On enregistre le nom du gagnant de la partie dans le fichier Fliptech.txt
			}
			else{
				fprintf(fichier, "Prenom : %s | score : %u \n", (a + i)->prenom, (a + i)->score);
			}
		}
	}
	fclose(fichier);
}

