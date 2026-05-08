#include <stdbool.h>
#include <string.h>
#include "structure.h"
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
		for(unsigned int i = 1; i < strlen(prenom); i++){
			if(prenom[i] != '\0' && (prenom[i] > 64 && prenom[i] < 91)){
					prenom[i] -= 'A' - 'a'; 
			}
		}
	}
}

// Verifie la validité du prénom du joueur
bool PrenomValide(char* prenom){
	for(unsigned int i = 0; i < strlen(prenom); i++){
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
	}
	return score;
}

// Calcule le score du joueur a la fin de son tour
void CalculScore(Perso* joueurs, Carte* main, int taille,bool doublon){
			if(joueurs == NULL || taille <= 0){
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
			if(doublon){
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
	if(joueurs == NULL || nbjoueur < 3){
		printf("Erreur \n");
		exit(160);
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
		printf("\n 	Le gagnant est : %s  avec un score de  %u   \n",adresseMax->prenom, max);
	 
		 //On retourne l'adresse du joueur qui a gagné
		 return adresseMax;
}

//On enregistre le Nom de chaque gagnant de la partie
void Enregistrejoueurs(Perso* a, int nbjoueur){
	if(a == NULL || nbjoueur < 2){
            printf("Erreur\n");
            exit(5);
    }
	Perso* gagnant = designerGagnant(a, nbjoueur);

	//On ouvre le fichier Fliptech.txt
	FILE* fichier = NULL; 
	fichier = fopen("Fliptech.txt", "w+"); 

	for(int i = 0; i < nbjoueur; i++){
		char choix;


		printf("\n %s veux tu enregistrer ton score sur le fichier Fliptech ? (oui : O / non : N) \n", (a + i)->prenom);
		while(scanf(" %c",&choix) != 1 && (choix != 'O' && choix != 'N')){ //Tant que l'utilisateur ne saisi pas 'O4 OU 'N' on lui redemande de saisir
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

/*
void CarteSpeciale(Perso* joueur, Perso* joueurs, int nbJoueurs, int special, Paquet* paquet, bool* doublon){
		if(joueurs == NULL || nbjoueur < 3 || (special < 1 || special > 3)){
                	printf("Erreur\n");
                	exit(1);
		}

		char prenom[TAILLE];
		bool trouve = false;
		
		//On compte combien de joueurs sont en =core dans la manche
		int encoreEnJeu = 0;
		for(int i = 0; i < nbJoueurs; i++){
					if((joueurs+i)->Ajouer == false){
							encoreEnJeu++;
					}
		}
		do{
			if(encoreEnJeu <= 1){
					printf("\n Vous êtes le seul joueur encore dans la manche, vous vous ciblez vous-même. \n");
					strcpy(prenom, joueur->prenom);
			}
			else{
					printf("\n %s, qui veux-tu stopper ? \n", joueur->prenom);
					while(scanf("%s", prenom) != 1 && PrenomValide(prenom) == false){
						printf("Saisi invalide, veuillez recommencer");
						while(getchar() != '\n'); //On vide le tampon
			}
			}
			for(int i = 0; i < nbJoueurs; i++){
			    // On compare les prénom pour voir si on trouve le joueur
				if(strcmp(prenom, (joueurs+i)->prenom) != 0){
					trouve = true;
					if((joueurs+i)->Ajouer == false ){
						(joueurs+i)->Ajouer = true; 
					}
					else{
						printf("Ce joueur a déjà joué, choisi en un autre \n");
						trouve = false; 
					}
					break; 
				}
			}
			if(!trouve && encoreEnJeu > 1){
				printf("\n Joueur introuvable, veuillez recommencer. \n");
			}
		}
}while(!trouve)
		
		// carte seconde chance
		if(special == 2){
			if(joueur->aScondechance == true){
				//il doit donner à un autre joueur qui n'en a pas
				bool donne = false;
			}
			for(int i = 0; i < nbjoueurs; i++){
					if((joueurs+i)->Ajouer == false && strcmp((joueurs+i)->prenom, joueur->prenom) != 0 && (joueurs+i)->aScondechance = false){
							(joueurs+i)->aScondechance = true;
							printf(" \n %s donne sa Seconde Chanche à %s. \n", joueur->prenom, (joueurs+i)->prenom);
							donne = true;
							break;
					}
			}
			if(!donne){
				printf("\n Pas de joueur disponible, la carte Seconde chance est défaussée. \n")
			}
			else{
				joueur->aScondechance = true;
			    printf("\n %s obtient une Seconde Chance ! \n", joueur->prenom);
			
			}
		}

		// --- carte trois à la suite ---
		if(special == 3){

			do{
				trouve = false;
				printf("\n %s, qui veux tu cibler (peut-être toi-même) ? \n", joueur->prenom);
				while(scanf("%s", prenom) != 1 && PrenomValide(prenom) == false){
					printf("Saisi invalide, veuillez recommencer");
					while(getchar() != '\n'); //On vide le tampon
				}

				for(int i = 0; i < nbjoueurs; i++){
					if(strcmp((joueurs+i)->prenom, joueur->prenom) == 0){
						if((joueurs+i)->Ajouer == false){	
							trouve = true
							printf("\n Distribution de 3 cartes à %s: \n", (joueurs+i)->prenom);

							int carteDistrib = 0;
							bool specialPendant = false;
							carte carteSpecialeTrouvee;

							while(carteDistrib < 3 && !(doublon[i]) && !Flip7(joueurs[i])){
									carte c = piocher(paquet);
									afficherCarte(c);

									if(c.type == 'S'){
									// Carte trouvee pendant l'effet : on la garde et l'applique à la fin sauf si il y a eu un flip 7 ou un doublon avant

									specialPendant =  true;
									carteSpecialTrouvee = c;
									cartesdDistrib++;
									continue; // Va a la prochaine itération directement
									
									}

									if(!NoDoublon(c, joueurs[i])){
										printf("%s saute ! Distribution arrêtée. \n", (joueurs+i)->prenom);

										doublon[i] = true;
										// Si une carte special à été révélée pendant l'effet le joueur doit sibler quelqu'un
										if(specialPendant){
											printf("Une carte speciale avait été révélée, %s doit cibler un autre joueur. \n", (joueurs+i)->prenom)
											CarteSpeciale(joueurs+i, joueurs, nbJoueurs, carteSpecialeTrouvee.special, paquet, doublon);
										}
										else{
											(joueurs+i)->carte[(joueurs+i)->nbcarte] = c;
											(joueurs+i)->nbcarte++;
											carteDistrib++;
										}

										if(Flip7(joueurs[i])){
											printf("\n FLIP 7 ! Distribution arrêtée. \n");
											if(specialPendant){
													CarteSpeciale(joueurs+i, joueurs, nbJoueurs, carteSpecialeTrouvee.special, paquet, doublon);
											}

										}
									}
									// On applique la carte speciale après les 3 cartes si pas de saut
									if(specialPendant && !doublon[i] && !Flip7(joueurs[i])){
										CarteSpeciale(joueurs+i, joueurs, nbJoueurs, carteSpecialeTrouvee.special, paquet, doublon);
									}
									else{
										printf("Ce joueur a déjà joué, choisis-en un autre. \n");
									}
									break;
								}
							}
							if(!trouve){
								printf("Joueur introuvable ! Veuillez recommencer \n");
							}
			}while(!trouve)
}
*/