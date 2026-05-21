#ifndef AFFICHAGE_H // Garde d'inclusion pour éviter les inclusions multiples
#define AFFICHAGE_H

#include "structure.h"
#include <stdbool.h>


// Remise à zero des styles appliqués
#define RESET "\033[0m"

// Styles
#define GRAS "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"

// Couleurs pour le texte
#define JAUNE "\033[33m"
#define CYAN "\033[36m"

// Couleurs Vives pour le texte
#define V_NOIR "\033[90m"
#define V_ROUGE "\033[91m"
#define V_VERT "\033[92m"
#define V_JAUNE "\033[93m"
#define V_BLEU "\033[94m"
#define V_MAGENTA "\033[95m"
#define V_CYAN "\033[96m"
#define V_BLANC "\033[97m"

// Emoji
#define EMOJI_BLESSURE "🤕"
#define EMOJI_CARTE "🃏"
#define EMOJI_ETOILE "⭐"
#define EMOJI_FEU "🔥"
#define EMOJI_JOUEUR "🧑"
#define EMOJI_MELANGE "🔀"
#define EMOJI_NOTE "📋"
#define EMOJI_SCORE "📊"
#define EMOJI_TROPHEE "🏆"
#define EMOJI_STOP "⛔"
#define EMOJI_ECRIRE "📝"

int largeurTerminal();
int calculeLargeurUtf8(char *chaine);
void effacerEcran();
void afficherSeparateur(int largeur);
void afficherTitrePrincipal();
void afficherCarteEsthetique(Carte c);
void afficherTableauScores(Perso *joueur, Perso *joueurs, int nbJoueurs);
void afficherNbcarte(Paquet *p);
void afficherJoueur(char *prenom);
void afficherGagnant(char *prenom);
void afficherStatut(Perso *joueurs, int nbJoueurs);

#endif // Fin de la garde d'inclusion