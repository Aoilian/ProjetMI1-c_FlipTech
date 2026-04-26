#ifndef STRUCTURE_H //Garde d'inclusion pour éviter les inclusions multiples
#define STRUCTURE_H 


typedef struct {
    char type; // 'N' = carte numéro, 'B' = carte bonus
    int numero;  // de 12 à 0 
    int bonus; // 6 cartes bonus 
} Carte;

typedef struct{
	Carte carte[7];
	unsigned int score;
	unsigned int nbcarte;
	char prenom[255];
}Perso;

typedef struct {
    Carte cartes[85];
    int nbCartes; // nombre de cartes restantes dans la pile
} Paquet;

typedef struct {
    int nbNumero; // nombre de cartes numéro piochées
    int nbBonus; // nombre de cartes bonus piochées
    int nbSpeciale; // nombre de cartes spéciale piochées
} Stats;


#endif //Fin de la garde d'inclusion
