#ifndef AFFICHAGE_H //Garde d'inclusion pour éviter les inclusions multiples
#define AFFICHAGE_H 
#include <stdbool.h>
#include "structure.h"

/* Remise à zero */
#define RESET "\033[0m"

/* Styles */
#define GRAS "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define SOULIGNER "\033[4m"
#define CLIGNOTE "\033[5m"


/* Couleurs de textes */
#define JAUNE "\033[33m"
#define CYAN "\033[36m"

/* Couleurs du fond*/
#define F_BLANC "\033[47m"

/* Couleurs Vives */
#define V_NOIR "\033[90m"
#define V_JAUNE "\033[93m"
#define V_VERT "\033[92m"
#define V_ROUGE "\033[91m"
#define V_BLEU "\033[95m"
#define V_MAGENTA "\033[95m"
#define V_BLANC "\033[97m"
#define V_CYAN "\033[96m"

/* Emoji */
#define EMOJI_CARTE "🃏"
#define EMOJI_SCORE "📊"
#define EMOJI_MELANGE "🔀"
#define EMOJI_ETOILE "⭐"
#define EMOJI_FEU "🔥"
#define EMOJI_TROPHEE "🏆"
#define EMOJI_JOUEUR "🧑"


/* Caractère de tracé de boites */
#define BOITE_HG "╔" // Coin haut gauche 
#define BOITE_HD " ╗" // Coin haut droite
#define BOITE_BG "╚" // Coin bas gauche
#define BOITE_BD "╝" // Coin bas droite
#define BOITE_CR "╬" // Croissement
#define BOITE_V "║"  // vertical
#define BOITE_H "═" // horizontale
#define BOITE_PLEINE "█"
#define BOITE_M "░"


void effacerEcran();
void afficherSeparateur(int largeur);
void afficherTitrePrincipal();
void afficherCarteEsthetique(Carte c);
void afficherTableauScores(Perso* joueur, Perso* joueurs, int nbJoueurs);
void afficherPaquet(Paquet* p);
void afficherStat(Stats statistiques);
void afficherNbcarte(Paquet* p);
void afficherGagnant(char* prenom, unsigned int score);


#endif //Fin de la garde d'inclusion