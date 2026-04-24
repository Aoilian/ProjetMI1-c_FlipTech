#include <stdio.h>
#define TAILLE 255
#define MAIN

typedef struct{
	char prenom[TAILLE];
	unsigned int score;
	unsigned int nbcarte;
	unsigned int carte[MAIN];
	bool Ajouer;
}Perso;

//Est-ce que l'utilisateur va piocher?
void decision(int* piocher,Perso* joueur){
	int valide = 0;
     
	do{
		printf("Voulez-vous piocher ? \n- oui : 1, \n- non : 0\n");
		
        	//verification si scanf a bien marché, et si le nombre est respecté
        	if (scanf("%d", piocher) == 1 && (*piocher == 0 || *piocher == 1)) {
            		valide = 1; //si c'est valide, c'est fini
        }else{
        	printf("Erreur : saisie invalide.\n");
        	//On vide le tampon au cas où l'utilisateur aurais tapé un caractère
        	while (getchar() != '\n'); 
        	}
        
    	}while (valide == 0); //On recommence tant que ce n'est pas valide
    
	joueur->Ajouer = true;   

}    
    
    
    
    
//nombre de joueurs dans la partie ?
void nmbJoueurs(int* nbJoueurs){
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

bool MancheTerminer(Perso* joueurs, int nbjoueur){
	for(int i = 0; i < nbjoueur; i++){
		if((joueurs+i)->Ajouer == false){
			return false;
		}
	}
	return true;
}

void lancerManche(Perso* Joueurs, int nbJoueurs) { //Joueurs => tous les joueurs de la partie
	//On choisit qui commence (aléatoire)
	int joueurActuel = rand() % nbJoueurs;
	int toursCompletes = 0;

	printf("\n--- LA MANCHE COMMENCE ---\n");
	printf("Le hasard a choisi : %s commence !\n", listeJoueurs[joueurActuel].prenom);

	//boucle de la manche : tant que tout le monde n'a pas fini son tour
	while (!MancheTerminer(listeJoueurs, nbJoueurs)) {
        
        // On ne fait jouer le joueur que s'il n'a pas encore joué
        	if (Joueurs[joueurActuel].Ajouer == false) {
        		printf("\nC'est au tour de %s !\n",Joueurs[joueurActuel].prenom);
        		// jouerTourDuJoueur(&listeJoueurs[joueurActuel]); 
            
        		// Une fois qu'il a fini (stop ou bust), on marque qu'il a joué
        		Joueurs[joueurActuel].Ajouer = true;
        	}

        	// on passe au joueur suivant
        	joueurActuel = (joueurActuel + 1) % nbJoueurs;
    	}
	
	printf("\nFin de la manche ! Tout le monde a joue.\n");
}


void enregistrerJoueurs(Perso* joueurs, int n) {
    for(int i = 0; i < n; i++) {
        printf("\n--- Joueur %d ---\n", i + 1);
        printf("Nom : ");
        scanf("%s", joueurs[i].prenom); // On stocke dans la i-ème case
        
        // initialisation du score, etc, à 0;
        joueurs[i].score = 0;
        joueurs[i].nbcarte = 0;
        joueurs[i].Ajouer = false; // ou 0 ??
    }
}

int main(){
	int piocher;
	int nbJoueur;
	decision(&piocher);
	nmbJoueurs(&nbJoueur);
	return 0;
}

/*
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
