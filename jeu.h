/*--------------------------------------------------------------
|                          Jeu.h                               |
|      Contient les prototypes des fonctions pour jeu .c       |
|                                                              |
|                                                              |
---------------------------------------------------------------*/

#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/*Nombres de pickominos max*/
#define MAXSIZE 16

/*Struct joueur */
typedef struct _Player
{
    int numPlayer;
    char name[32];
    int score;
    int stack[16][2];
    int top;
    int type; /*0 = humain , 1 = IA*/
} player;

/*Struct pickominos avec leurs numéro (num) et valeur */
typedef struct _Pickomino
{
    short num;
    short valeur;
} pickomino;

/*Struct Dice qui gère les dés choisis par un joueur*/
/*nbr = nombres gardé*/
/*acc = nombres de nombres gardé*/
/*Somme de nbr*/
typedef struct _Dice
{
    short nbr[9];
    short acc;
    short sum;
} Dice;
/*Pile*/

/*Fonctions INIT*/

/*Initialise les pickominos*/
void initPickomino(struct _Pickomino *pickominos);
/*Initialise les joueurs */
void initPlayers(struct _Player *players, short *pNbrPlayers);
/*Met a 0 les joueurs */
void clearPlayers(struct _Player *players, int i);
/*Re initialise Dice  */
void clearDice(struct _Dice *Dice);

/*Fonctios liés aux pickominos*/

/*Affiches les pickominos*/
void drawPikomino(struct _Pickomino *pickominos);
/*Renvoi le numéro du pickomino*/
short getPickominoNumber(struct _Pickomino *pickominos, int i);
/*Renvoi la valeur du pickomino*/
short getPickominoValue(struct _Pickomino *pickominos, int i);
/*Renvoi le numéro du pickomino d'un joueur*/
short getPlayerPickominoNumber(struct _Player *players, short i);
/*Renvoi la valeur du pickominos d'un joueur*/
short getPlayerPickominoValue(struct _Player *players, short i);
/*Passe la valeur du pickomino avec le plus haut nombre a -1*/
void deleteHighestPickomino(struct _Pickomino *pickominos);
/*Joueur 'j' récupère le pickomino du joueur 'i'*/
void stealPickomino(struct _Player *players, int i, int j);
/*Renvoi le pickomino demandé*/
short currentPickomino(int x);

/*Fonctions liés au joueurs et au déroulement de la partie*/

/*Fonction principale qui gère le tour en cours */
int launch(short *pNbrDice, struct _Pickomino *pickominos, struct _Player *players, short *numPlayer, short *pNbrPlayers, int res);
/*Vérifie si le tour actuel est valide ou si il ne reste pas les règles*/
short checkBadTurn(struct _Dice *Dice, struct _Player *players, struct _Pickomino *pickominos, short *numPlayer);
/*Vérifie quel pickomino est disponible en fonction de la somme des dés du joueur*/
void checkAvailablePickomino(struct _Pickomino *pickominos, struct _Dice *Dice, struct _Player *players, short *numPlayer, short *pNbrPlayers);
/*Renvoi la somme des dés choisis par un joueur*/
void sumPickomino(struct _Player *players, short *numPlayer);
/*Renvoi le plus petit pickomino différent de -1*/
short checkMin(struct _Pickomino *pickominos);
/*Renvoi le plus grand pickomino différent de -1*/
short checkMax(struct _Pickomino *pickominos);
/*Remet en jeu le pickomino de numéro x*/
void replace(struct _Pickomino *pickominos, short x);
/*Récupère le gagant de la partie en fonction de leurs score*/
void getWinner(struct _Player *players, short *pNbrPlayers);
/*Calcul le score de chaque joueur*/
void calculateWin(struct _Player *players, short *pNbrPlayers);
/*Vérifie si le chiffre choisis est dans les dés*/
short isIn(short *dice, short *pNbrDice, short x);
/*Vérifie si le chiffre choisis est dans les dés mis de coté*/
short isInChoice(struct _Dice *Dice, short x);
/*Vérifie si un choix est encore possible en fonction des dés mis de coté et des dés lancé*/
short isChoicePossible(struct _Dice *Dice, short *dice, short *pNbrDice);
/*Dés*/
/*Renvoi les dés lancé, nbrDice est le nombre de dés qui doivent être lancé*/
short *diceRoll(short *nbrDice);
/*Affiche les dés lancé*/
void printDice(short *dice);
/*Permet a un joueur de choisir des dés*/
void numberChoice(short *dice, short *nbrDice, struct _Dice *Dice);
/*Renvoi tout les dés qui ont été choisis par le joueur*/
short *check(short *dice, short *nbrDice, short *tmp);
/*Permet d'eviter des printf a l'infini en cas d'une mauvaise valeur entré*/
void buffer(FILE *stream);

/*Ajoute les dés choisis dans une struct qui garde les choix afin d'en faire la somme dans la fonction sumDice*/
void add(struct _Dice *Dice, short *tmp);
/*Fait la somme de toute les valeurs contenue dans Dice*/
void sumDice(struct _Dice *Dice);
/* Verifie si la pile est vide isEmpty(struct _Player, numéro joueur)*/
int isEmpty(struct _Player *players, int i);
/* Verifie si la pile est pleine isFull( struct _Player, numéro joueur)*/
int isFull(struct _Player *players, int i);
/* Retire le pickomino en haut de la pile pop( struct _Player, numéro joueur) */
short pop(struct _Player *players, int i);
/* Pose un pickomino sur le haut de la pile : push(struct _Player, numéro joueur, numéro du picko, valeur du picko)*/
void push(struct _Player *players, short i, short data, short data2);


/*Fonctions de sauvegarde et de lecture, non fonctionnel*/
void savef(struct _Player *players, struct _Pickomino *pickominos, struct _Dice *Dice, short *pNbrPlayers);
void readf(struct _Player *players, struct _Pickomino *pickominos);

/*Fonctions lié a l'IA */

/*choix de l'IA*/
void choiceIA(short *dice, short *pNbrDice, struct _Dice *Dice);
/*Tour de l'IA*/
int launchIA(short *pNbrDice, struct _Pickomino *pickominos, struct _Player *players, short *numPlayer, short *pNbrPlayers, int res);

#endif