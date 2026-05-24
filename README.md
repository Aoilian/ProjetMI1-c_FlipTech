# FLIPTECH - jeu de carte

Ce projet est un jeu de carte interactif développé en C dans le cadre de notre projet de fin d'année d'informatique

## 🎮 présentation du jeu 
Le FLIPTECH, c’est un jeu de cartes qui se joue avec 3 joueurs minimum. L’objectif des joueurs est d'accumuler un maximum de points jusqu’à la fin de la partie. La partie prend fin si un des joueurs atteint 200 points ou si le paquet de cartes est vide. Le paquet de cartes est composé de 79 cartes numéro (12 cartes 12, 11 carte 11, etc…), 6 cartes bonus (+2/4/6/8/10, *2) et une carte spéciale le STOP, qui permet d’arrêter la manche d’un joueur. Les joueurs peuvent décider de piocher à nouveau mais attention s’ils piochent une carte qu’ils possèdent déjà alors ils sont éliminés de la manche et ne marquent aucun point, en revanche s'ils réussissent à avoir dans leur main 7 cartes numéro différentes, la manche s’arrête et ils marquent 15 points bonus ou ils peuvent décider de stopper leur manche en gardant les points qu’ils ont accumulés durant celle-ci. 

## 🚀 Comment lancer le jeu ?

* Un compilateur C (`gcc`)
* L'outil `make`
* Un terminal compatible UTF-8 (pour l'affichage des émoji  et des accents)

### compilation
Pour compiler le projet grâce au Makefile, exécuter simplement :
```make