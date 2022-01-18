#include "jeu.h"
int main(int argc, char **argv)
{
    int res = 16;
    short winner = 0;
    short nbrPlayers = 0;
    short *pNbrPlayers = &nbrPlayers;

    short nbrDice = 8;
    short *pNbrDice = &nbrDice;

    struct _Player players[7];
    struct _Pickomino pickominos[16];

    short currentPlayer = 0;
    short *pCurrentPlayer = &currentPlayer;

    srand(time(0));
    initPickomino(pickominos);
    initPlayers(players, pNbrPlayers);

    while (!(winner))
    {
        if (players[*pCurrentPlayer].type == 0)
        {
            res = launch(pNbrDice, pickominos, players, pCurrentPlayer, pNbrPlayers, res);
        }
        else if (players[*pCurrentPlayer].type == 1)
        {
            res = launchIA(pNbrDice, pickominos, players, pCurrentPlayer, pNbrPlayers, res);
        }

        *pNbrDice = 8;
        if (*pCurrentPlayer >= *pNbrPlayers)
        {
            *pCurrentPlayer = 0;
        }
        if (!(res))
        {
            printf("Fin de la partie\n");
            getWinner(players, pNbrPlayers);
            winner = 1;
        }
    }
    return 0;
}