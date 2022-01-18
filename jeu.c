#include "jeu.h"

int cSupEsq = 218; /*'┌'*/
int cSupDir = 191; /*'┐'*/
int cInfEsq = 192; /*'└'*/
int cInfDir = 217; /*'┘'*/
int mVert = 179;   /*'│'*/
int mHor = 196;    /*'─'*/
int barreG = 180;
int barreD = 195;

void initPickomino(struct _Pickomino *pickominos)
{
    short z = 21;
    short k = 0;
    short i;
    for (i = 0; i < 16; i++)
    {
        pickominos[i].num = z;
        z++;
        if (!(i % 4))
            k++;
        pickominos[i].valeur = k;
    }
}
void initPlayers(struct _Player *players, short *pNbrPlayers)
{
    short x = 0;
    short i;
    for (i = 0; i < 7; i++)
    {
        players[i].top = -1;
        players[i].score = 0;
        players[i].numPlayer = 0;
        players[i].type = 0;
        clearPlayers(players, i);
    }
err:
    printf("Entrer le nombre de joueur ");
    fscanf(stdin, " %hd", pNbrPlayers);
    buffer(stdin);
    if (*pNbrPlayers < 2 || *pNbrPlayers > 7)
    {
        printf("Veuillez entrer un nombre de joueur valide ( 2-7 )\n");
        goto err;
    }
    printf("Combien de joueur IA present ?");
    fscanf(stdin, " %hd", &x);
    buffer(stdin);

    for (i = 0; i < *pNbrPlayers; ++i)
    {
        if (i < (*pNbrPlayers - x))
        {
            players[i].numPlayer = i + 1;
            printf("\nEntrer le nom du joueur %d ", i + 1);
            scanf(" %[^\n]s", players[i].name);
            buffer(stdin);
        }
        else
        {
            players[i].numPlayer = i + 1;
            printf("\nEntrer le nom du joueur IA %d ", i + 1);
            scanf(" %[^\n]s", players[i].name);
            buffer(stdin);
            players[i].type = 1;
        }
    }
}
void clearPlayers(struct _Player *players, int i)
{
    short x;
    for (x = 0; x < 16; x++)
    {
        players[i].stack[x][0] = 0;
        players[i].stack[x][1] = 0;
    }
}
void drawPikomino(struct _Pickomino *pickominos)
{
    short i;
    for (i = 0; i <= 15; i++)
    {
        if (pickominos[i].num == -1)
        {
            printf("#### ");
        }
        else
        {
            printf("%c%c%c%c ", cSupEsq, mHor, mHor, cSupDir);
        }
    }
    putchar('\n');
    for (i = 0; i <= 15; i++)
    {
        if (pickominos[i].num == -1)
        {
            printf("#### ");
        }
        else
        {
            printf("%c%d%c ", mVert, pickominos[i].num, mVert);
        }
    }
    putchar('\n');
    for (i = 0; i <= 15; i++)
    {
        if (pickominos[i].num == -1)
        {
            printf("#### ");
        }
        else
        {
            printf("%c%c%c%c ", barreD, mHor, mHor, barreG);
        }
    }
    putchar('\n');
    for (i = 0; i <= 15; i++)
    {
        if (pickominos[i].num == -1)
        {
            printf("#### ");
        }
        else
        {
            printf("%c %d%c ", mVert, pickominos[i].valeur, mVert);
        }
    }
    putchar('\n');
    for (i = 0; i <= 15; i++)
    {
        if (pickominos[i].num == -1)
        {
            printf("#### ");
        }
        else
        {
            printf("%c%c%c%c ", cInfEsq, mHor, mHor, cInfDir);
        }
    }
    putchar('\n');
}
void clearDice(struct _Dice *Dice)
{
    int i;
    Dice->acc = 0;
    Dice->sum = 0;
    for (i = 0; i < 9; i++)
    {
        Dice->nbr[i] = 0;
    }
}
short *diceRoll(short *pNbrDice)
{
    short n;
    int x = 0;
    short *dice = calloc(*pNbrDice, sizeof(short));
    for (n = 0; n != *pNbrDice; ++n)
    {
        x = 7;
        while (x > 6)
            x = 1 + (rand() % 6);
        dice[n] = x;
    }
    dice[n] = -1;
    return dice;
}
void printDice(short *dice)
{
    int i = 0;
    printf("\nLes des sont : ");
    while (dice[i] != -1)
    {
        if (dice[i] == 6)
        {
            printf("V\t");
        }
        else
        {
            printf("%d\t", dice[i]);
        }
        i++;
    }
    printf("\n");
}
short isChoicePossible(struct _Dice *Dice, short *dice, short *pNbrDice)
{
    short i = 0;
    short j = 0;
    short dejapris = 0;
    short nboccurence = 0;
    while (dice[i] != -1)
    {
        while (Dice->nbr[j] != 0)
        {
            if (Dice->nbr[j] == dice[i] && dejapris == 0)
            {
                dejapris = 1;
                nboccurence++;
            }
            j++;
        }
        j = 0;
        i++;
        dejapris = 0;
    }
    if (nboccurence == *pNbrDice)
    {
        return 0;
    }
    return 1;
}
void numberChoice(short *dice, short *pNbrDice, struct _Dice *Dice)
{
    char *y = calloc(10, sizeof(char));
    short i = 0;
    short x=0;
    short test = 0;
err:
    printf("Chiffre choisis:\t");
    fscanf(stdin, "%s", y);
    buffer(stdin);
    test = (short)y[0];
    switch (test)
    {
    case 49:
        x = 1;
        break;
    case 50:
        x = 2;
        break;
    case 51:
        x = 3;
        break;
    case 52:
        x = 4;
        break;
    case 53:
        x = 5;
        break;
    case 86:
        x = 6;
        break;
    case 118:
        x = 6;
        break;
    }

    if (!(isIn(dice, pNbrDice, x)))
    {
        printf("Veuillez entre un nombre qui est dans les des \n");
        goto err;
    }
    if (!(isInChoice(Dice, x)))
    {
        printf("Veuillez entre un nombre qui n'est pas deja choisis \n");
        goto err;
    }

    while (dice[i] != -1)
    {
        if (dice[i] != x)
        {
            dice[i] = 0;
        }
        else
        {
            --(*pNbrDice);
        }
        ++i;
    }
    printf("Il vous reste %d des a lancer.", *pNbrDice);
}
short *check(short *dice, short *pNbrDice, short *tmp)
{
    short i = 0;
    short x = 0;
    while (dice[i] != -1)
    {
        if (dice[i] != 0)
        {
            tmp[x] = dice[i];
            x++;
        }
        ++i;
    }
    tmp[x] = -1;
    return tmp;
}
void add(struct _Dice *Dice, short *tmp)
{
    int i = 0;
    while (tmp[i] != -1)
    {
        if (tmp[i] != 0)
        {
            Dice->nbr[Dice->acc] = tmp[i];
            Dice->acc = Dice->acc + 1;
        }
        ++i;
    }
}
void sumDice(struct _Dice *Dice)
{
    short i;
    short sum = 0;
    for (i = 0; i < Dice->acc; i++)
    {
        if (Dice->nbr[i] == 6)
            sum += 5;
        else
        {
            sum += Dice->nbr[i];
        }
    }
    Dice->sum = sum;
}
void checkAvailablePickomino(struct _Pickomino *pickominos, struct _Dice *Dice, struct _Player *players, short *numPlayer, short *pNbrPlayers)
{

    short i;
    short x = 0;
    short y = 0;
    i = 0;

    if (pickominos[currentPickomino(Dice->sum)].num != -1)
    {
        push(players, *numPlayer, pickominos[currentPickomino(Dice->sum)].num, pickominos[currentPickomino(Dice->sum)].valeur);
        printf("Vous avez maintenant le pickominos : %d\n", pickominos[currentPickomino(Dice->sum)].num);
        pickominos[currentPickomino(Dice->sum)].num = -1;
    }
    else
    {
        for (i = 0; i < *pNbrPlayers; i++)
        {
            if (i == *numPlayer)
            {
                continue;
            }

            x = getPlayerPickominoNumber(players, i);
            y = getPlayerPickominoValue(players, i);
            if (x == Dice->sum)
            {
                push(players, *numPlayer, x, y);
                printf("Vous avez maintenant le pickominos : %d de %s\n", pickominos[i].num, players[i].name);
                pop(players, i);
                break;
            }
            else
            {
                for (i = Dice->sum - 21; i >= 0; i--)
                {
                    if (pickominos[i].num > pickominos[currentPickomino((int)Dice->sum)].num)
                    {
                        push(players, *numPlayer, getPickominoNumber(pickominos, i), getPickominoValue(pickominos, i));
                        printf("Vous avez maintenant le pickominos : %d\n", pickominos[i].num);
                        pickominos[i].num = -1;
                        break;
                    }
                }
            }
        }
    }
}
short checkBadTurn(struct _Dice *Dice, struct _Player *players, struct _Pickomino *pickominos, short *numPlayer)
{

    short i = 0;
    short tmp = 0;
    short badTurn = 0;

    if (Dice->sum < checkMin(pickominos) || Dice->sum > 36)
    {
        for (i = 0; i < currentPickomino(Dice->sum); i++)
        {
            if (pickominos[i].num == -1)
            {
                tmp++;
            }
        }

        printf("Tour perdu, somme des des invalide : %d\n", Dice->sum);
        badTurn = 1;
        goto bad;
    }
    while (i < Dice->acc)
    {
        if (Dice->nbr[i] == 6)
        {
            tmp++;
        }
        i++;
    }
    if (tmp == 0)
    {
        printf("Vous n'avez pas pris de V\n");
        badTurn = 1;
    }
bad:
    if (badTurn)
    {
        if (players[*numPlayer].top != -1)
        {
            short x;
            x = pop(players, *numPlayer);
            replace(pickominos, x);
        }
        deleteHighestPickomino(pickominos);
        return 0;
    }
    return 1;
}
int launch(short *pNbrDice, struct _Pickomino *pickominos, struct _Player *players, short *numPlayer, short *pNbrPlayers, int res)
{
    short *tmp;
    short *dice;
    int y;
    short x;
    short n;
    char c[20];
    struct _Dice *DicePtr, Dice = {0};
    int pickominosAvailable;
    pickominosAvailable = res;
    DicePtr = &Dice;
    drawPikomino(pickominos);
    clearDice(DicePtr);
    printf("Au tour de %s de jouer\n", players[*numPlayer].name);
start:
    tmp = calloc(*pNbrDice, sizeof(short));
    dice = diceRoll(pNbrDice); /* Lance les dés */
    printDice(dice);
    if (!(isChoicePossible(DicePtr, dice, pNbrDice)))
    {
        x = pop(players, *numPlayer);
        if ((x))
        {
            replace(pickominos, x);
            pickominosAvailable += 1;
        }
        printf("Vous n'avez plus aucun choix possibles, tour rate\n");
        deleteHighestPickomino(pickominos);
        goto test2;
    }
    numberChoice(dice, pNbrDice, DicePtr); /* Choix du joueur */
    tmp = check(dice, pNbrDice, tmp);      /* Met 0 dans les chiffres non choisis par le joueur*/

    add(DicePtr, tmp);
    putchar('\n');
    /*save(players, pickominos, DicePtr, pNbrPlayers);     /!\ source de crash         */
    if (*pNbrDice == 0)
    {
        goto test;
    }
err:
    printf("\nVoulez vous relancer les des ? (y/n)\n");
    fscanf(stdin, " %s", c);
    buffer(stdin);
    y = strcmp(c, "y");
    n = strcmp(c, "n");
    if (y == 0)
        goto start;
    else if (*pNbrDice == 0)
    {
        return 1;
    }
    else if (n == 0)
    {
    test:
        sumDice(DicePtr);
        if (checkBadTurn(DicePtr, players, pickominos, numPlayer))
        {
            checkAvailablePickomino(pickominos, DicePtr, players, numPlayer, pNbrPlayers);
        }
    test2:
        pickominosAvailable--;
        (*numPlayer)++;
        printf("\n Il reste %d pickominos en jeu \n", pickominosAvailable);
        return pickominosAvailable;
    }
    else
    {
        printf("\nMauvais format utiliser : (y/n)\n");
        goto err;
    }
    return 1;
}
void getWinner(struct _Player *players, short *pNbrPlayers)
{
    short max[1] = {0};
    short j = 0;
    short i;
    calculateWin(players, pNbrPlayers);
    for (i = 0; i < *pNbrPlayers; ++i)
    {
        if (max[0] < players[i].score)
        {
            max[0] = players[i].score;
            j = players[i].numPlayer;
        }
    }
    i = 0;
    while (i <= *pNbrPlayers)
    {
        if (i == j)
        {
            printf("%s le joueur %d a gagne la partie avec %d points\n ", players[j - 1].name, players[j - 1].numPlayer, players[j - 1].score);
            break;
        }
        i++;
    }
}
void calculateWin(struct _Player *players, short *pNbrPlayers)
{
    short i;
    short acc = 0;
    for (i = 0; i < *pNbrPlayers; i++)
    {
        while (players[i].top != -1)
        {
            acc += getPlayerPickominoValue(players, i);
            pop(players, i);
        }
        players[i].score = acc;
        acc = 0;
    }
}
void sumPickomino(struct _Player *players, short *numPlayer)
{
    short sum = 0;
    short i;
    for (i = 0; i <= players[*numPlayer].top; i++)
    {
        sum += getPlayerPickominoValue(players, *numPlayer);
        players[*numPlayer].top--;
    }
    players[*numPlayer].score = sum;
}
void deleteHighestPickomino(struct _Pickomino *pickominos)
{
    short i;
    for (i = currentPickomino(checkMax(pickominos)); i >= 0; i--)
    {
        if (pickominos[i].num != -1)
        {
            printf("Le pickomino %d est maintenant invalide", pickominos[i].num);
            pickominos[i].num = -1;
            /*pickominos[i].valeur = -1;*/
            break;
        }
    }
}
short checkMin(struct _Pickomino *pickominos)
{
    short i;
    for (i = 0; i < 16; i++)
    {
        if (pickominos[i].num != -1)
        {
            return getPickominoNumber(pickominos, i);
        }
    }
    return 1;
}
short checkMax(struct _Pickomino *pickominos)
{
    short i;
    for (i = 15; i >= 0; i--)
    {
        if (pickominos[i].num != -1)
        {
            return getPickominoNumber(pickominos, i);
        }
    }
    return 1;
}
void replace(struct _Pickomino *pickominos, short x)
{
    short i;
    for (i = 0; i < 16; i++)
    {
        if (pickominos[currentPickomino(i)].num == -1)
        {
            pickominos[i].num = x;
            break;
        }
    }
}
short isIn(short *dice, short *pNbrDice, short x)
{
    short i;
    short tmp = 0;

    for (i = 0; i < *pNbrDice; i++)
    {
        if (dice[i] == x)
        {
            tmp++;
        }
    }
    if (tmp == 0)
    {
        return 0;
    }
    return 1;
}
short isInChoice(struct _Dice *Dice, short x)
{
    short i;
    short tmp = 0;

    if (Dice->nbr[0] == 0)
    {
        return 1;
    }

    for (i = 0; i <= Dice->acc; i++)
    {
        if (Dice->nbr[i] == x)
        {
            tmp++;
        }
    }

    if (tmp == 0)
    {
        return 1;
    }
    return 0;
}
void stealPickomino(struct _Player *players, int i, int j)
{
    push(players, j, getPlayerPickominoNumber(players, i), getPlayerPickominoValue(players, i));
    pop(players, i);
}
int isEmpty(struct _Player *players, int i)
{
    if (players[i].top == -1)
        return 1;
    else
        return 0;
}
int isFull(struct _Player *players, int i)
{
    if (players[i].top == MAXSIZE)
        return 1;
    else
        return 0;
}
short currentPickomino(int x)
{
    return x - 21;
}
short getPlayerPickominoNumber(struct _Player *players, short i)
{
    return players[i].stack[players[i].top][0];
}
short getPlayerPickominoValue(struct _Player *players, short i)
{
    return players[i].stack[players[i].top][1];
}
short getPickominoNumber(struct _Pickomino *pickominos, int i)
{
    return pickominos[i].num;
}
short getPickominoValue(struct _Pickomino *pickominos, int i)
{
    return pickominos[i].valeur;
}
short pop(struct _Player *players, int i)
{
    short data;
    /*short data2;*/
    /*short dataMix[2];*/
    if (!isEmpty(players, i))
    {
        /*dataMix[0] = players[i].stack[players[i].top][0];
        dataMix[1] = players[i].stack[players[i].top][1];*/
        data = players[i].stack[players[i].top][0];
        players[i].stack[players[i].top][0] = 0;
        players[i].stack[players[i].top][1] = 0;
        players[i].top--;
        return data;
    }
    else
    {
        return 1;
    }
}
void push(struct _Player *players, short i, short data, short data2)
{
    if (!isFull(players, i))
    {
        players[i].top++;
        players[i].stack[players[i].top][0] = data;
        players[i].stack[players[i].top][1] = data2;
    }
}
void buffer(FILE *stream)
{
    char tmp;
    while ((tmp = fgetc(stream)) != '\n' && tmp != EOF)
        ;
}
void savef(struct _Player *players, struct _Pickomino *pickominos, struct _Dice *Dice, short *pNbrPlayers)
{
    int i;
    int j;
    FILE *f = fopen("save.txt", "wb");
    fprintf(f, "%d\n", *pNbrPlayers);
    for (i = 0; i < *pNbrPlayers; i++)
    {
        fprintf(f, "%d ", players[i].numPlayer);
        fprintf(f, "%s ", players[i].name);
        fprintf(f, "%d ", players[i].score);
        fprintf(f, "%d ", players[i].top);
        for (j = 0; j < 16; j++)
        {
            if (players[i].top == -1)
            {
                break;
            }
            else
            {
                fprintf(f, "%d ", getPlayerPickominoNumber(players, j));
            }
        }
        fputc('\n', f);
        for (j = 0; j < 16; j++)
        {
            if (players[i].top == -1)
            {
                break;
            }
            else
            {
                fprintf(f, "%d ", getPlayerPickominoValue(players, j));
            }
        }
        fputc('\n', f);
    }
    for (i = 0; i < 16; i++)
    {
        fprintf(f, "%d ", getPickominoValue(pickominos, i));
    }
    fputc('\n', f);
    for (i = 0; i < 16; i++)
    {
        fprintf(f, "%d ", getPickominoNumber(pickominos, i));
    }
    fclose(f);
}
/*
void readf(struct _Player *players, struct _Pickomino *pickominos)
{
    int nbrPlayers;
    FILE *fo = fopen("save.txt", "r");
    nbrPlayers = fgetc(fo);
    printf("%c", nbrPlayers);

    fscanf(fo, "%d %s %d %d", players[0].numPlayer, players[0].name, players[0].score, players[0].top);
    fclose(fo);
}*/

void choiceIA(short *dice, short *pNbrDice, struct _Dice *Dice)
{
    short i;
    short j;
    short valuemax = 0;
    short valuetemp = 0;
    short occurence = 0;
    short occurence2 = 0;
    short temp = 0;
    for (i = 0; i < *pNbrDice; i++)
    {
        if (isIn(Dice->nbr, pNbrDice, dice[i]) == 0)
        {
            for (j = 0; j < *pNbrDice; j++)
            {
                if (dice[j] == dice[i])
                {
                    occurence2++;
                }
            }
            valuetemp = dice[i];
            if (valuetemp == 6)
            {
                valuetemp = 5;
            }
            if (valuemax * occurence < valuetemp * occurence2)
            {
                occurence = occurence2;
                valuemax = valuetemp;
                temp = i;
            }
            occurence2 = 0;
        }
    }
    valuemax = dice[temp];
    i = 0;
    while (dice[i] != -1)
    {
        if (dice[i] != valuemax)
        {
            dice[i] = 0;
        }
        else
        {
            --(*pNbrDice);
        }
        ++i;
    }
}

int launchIA(short *pNbrDice, struct _Pickomino *pickominos, struct _Player *players, short *numPlayer, short *pNbrPlayers, int res)
{
    short *tmp;
    short *dice;
    short x;
    struct _Dice *DicePtr, Dice = {0};
    int pickominosAvailable;
    pickominosAvailable = res;
    DicePtr = &Dice;
    drawPikomino(pickominos);
    clearDice(DicePtr);
    printf("Au tour de l'IA %s de jouer\n", players[*numPlayer].name);
start:

    tmp = calloc(*pNbrDice, sizeof(short));
    dice = diceRoll(pNbrDice); /* Lance les dés */
    printDice(dice);
    if (!(isChoicePossible(DicePtr, dice, pNbrDice)))
    {
        x = pop(players, *numPlayer);
        if ((x))
        {
            replace(pickominos, x);
            pickominosAvailable += 1;
        }
        printf("Vous n'avez plus aucun choix possibles, tour rate\n");
        deleteHighestPickomino(pickominos);
        goto test2;
    }
    choiceIA(dice, pNbrDice, DicePtr);
    tmp = check(dice, pNbrDice, tmp);

    add(DicePtr, tmp);
    putchar('\n');
    /*save(players, pickominos, DicePtr, pNbrPlayers);*/
    if (*pNbrDice == 0)
    {
        goto test;
    }
    sumDice(DicePtr);
    if (Dice.sum < 21)
    {
        sleep(1);
        goto start;        
    }
    else
    {
    test:
        sumDice(DicePtr);
        if (checkBadTurn(DicePtr, players, pickominos, numPlayer))
        {
            checkAvailablePickomino(pickominos, DicePtr, players, numPlayer, pNbrPlayers);
        }
    test2:
        pickominosAvailable--;
        (*numPlayer)++;
        printf("\n Il reste %d pickominos en jeu \n", pickominosAvailable);
        free(dice);
        free(tmp);
        return pickominosAvailable;
    }
    return 1;
}