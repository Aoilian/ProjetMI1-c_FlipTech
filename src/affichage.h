#ifndef AFFICHAGE_H //Garde d'inclusion pour éviter les inclusions multiples
#define AFFICHAGE_H 
#include <stdbool.h>
#include "structure.h"

/* Remise à zero*/
#define RESET "\033[0m"

/* Styles */
#define GRAS "\033[1m"


/* Couleurs de textes*/
#define JAUNE "\033[33m"
#define CYAN "\033[36m"

/* Couleurs Vives*/
#define V_JAUNE "\033[93m"
#define V_ROUGE "\033[91m"
#define V_BLANC "\033[97m"
#define V_CYAN "\033[96m"

/* Emoji */
#define EMOJI_CARTE "🃏"
#define EMOJI_SCORE "📊"
#define EMOJI_MELANGE "🔀"
#define EMOJI_ETOILE "⭐"
#define EMOJI_FEU "🔥"



/* Caractère de tracé de boites */
#define BOITE_HG "╔" // Coin haut gauche 
#define BOITE_HD " ╗" // Coin haut droite
#define BOITE_BG "╚" // Coin bas gauche
#define BOITE_BD "╝" // Coin bas droite
#define BOITE_CR "╬" // Croissement
#define BOITE_V "║"  // vertical
#define BOITE_H "═" // horizontale

void effacerEcran();
void afficherSeparateur(int largeur);
void afficherTitrePrincipal();
void afficherCarteEsthetique(Carte c);
void afficherTableauScores(Perso* joueur,Perso* joueurs, int nbJoueurs);
void afficherPaquet(Paquet p);


#endif //Fin de la garde d'inclusion