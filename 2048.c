#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

int Map[4][4] = {0};
int i,j;

void PrintMap(void)
{
    printf("---------------------\n");
    for (i = 0; i < 4; i++)
    {
        printf("|");
        for (j = 0; j < 4; j++)
        {
            printf("%-4d|",Map[i][j]);
        }
        printf("\n---------------------\n");
    }
}

char PrintMenu(void)
{
    printf("=====================\n"
           "=  [ w ] to Up      =\n"
           "=  [ s ] to Down    =\n"
           "=  [ a ] to Left    =\n"
           "=  [ d ] to Right   =\n"
           "=  [ Q ] Exit       =\n"
           "=====================\n");
    return getch();
}

void DelZero(int DelMap[][4])
{
    int k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
           if (DelMap[i][j] == 0 && j != 4)
           {
               for (k = j; k < 4; k++)
               {
                   if (DelMap[i][k] != 0)
                   {
                       DelMap[i][j] = DelMap[i][k];
                       DelMap[i][k] = 0;
                       break;
                   } 
               }
           }
        }
    }
}

int PlusNum(int PlusMap[][4],int Oprated)
{
    int Num=0;
    for (i = 0; i < 4; i++)
    {
        if (Oprated == 1)
        {
            if (PlusMap[i][2] == PlusMap[i][3])
            {
                PlusMap[i][2] += PlusMap[i][3];
                PlusMap[i][3] = 0;Num++;
            }
            if (PlusMap[i][1] == PlusMap[i][2])
            {
                PlusMap[i][1] += PlusMap[i][2];
                PlusMap[i][2] = 0;Num++;
            }
            if (PlusMap[i][0] == PlusMap[i][1])
            {
                PlusMap[i][0] += PlusMap[i][1];
                PlusMap[i][1] = 0;Num++;
            }
        }else{
            if (PlusMap[i][0] == PlusMap[i][1])
            {
                PlusMap[i][0] += PlusMap[i][1];
                PlusMap[i][1] = 0;Num++;
            }
             if (PlusMap[i][1] == PlusMap[i][2])
            {
                PlusMap[i][1] += PlusMap[i][2];
                PlusMap[i][2] = 0;Num++;
            }
            if (PlusMap[i][2] == PlusMap[i][3])
            {
                PlusMap[i][2] += PlusMap[i][3];
                PlusMap[i][3] = 0;Num++;
            }
        }
    }
    return Num;
}

void Reversal(int ReMap[][4])
{
    int k;
    for (i = 0; i < 4; i++)
    {
        for (j = 3; j >= 0; j--)
        {
            if (ReMap[i][j] == 0 && j != 0)
            {
                for ( k = j; k >= 0; k--)
                {
                    if (ReMap[i][k] != 0)
                    {
                        ReMap[i][j] = ReMap[i][k];
                        ReMap[i][k] = 0;
                        break;
                    }
                }    
            }
        }
    }
}

void OprateWS(int Oprated)
{
    int WSMap[4][4] = {0};
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            WSMap[i][j] =  Map[j][i];
        }
    }
    DelZero(WSMap);
    PlusNum(WSMap,Oprated);
    DelZero(WSMap);
    if (Oprated == 1)
    {
        Reversal(WSMap);
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            Map[i][j] =  WSMap[j][i];
        }
    }
}

void OprateAD(int Oprated)
{
    DelZero(Map);
    PlusNum(Map,Oprated);
    DelZero(Map);
    if (Oprated == 1)
    {
        Reversal(Map);
    }
}

void MakeNum(void)
{
    srand((unsigned)time(NULL));
    int NoneList[10][2],NewNumList[4] = {2,2,4,4},NonePlace,k=0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (Map[i][j] == 0)
            {
                NoneList[k][0] = i;
                NoneList[k][1] = j;
                k++;
            }
        }
    }
    if (k>0)
    {
        for (i = 0; i < 2; i++)
        {
            NonePlace = (k>1)?rand()%k:0;
            Map[NoneList[NonePlace][0]][NoneList[NonePlace][1]] = NewNumList[rand() % 4];
            k--;
        }
    }
}

int GameOver(int Map[][4])
{
    int OvMap[4][4];
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            OvMap[i][j] = Map[i][j];    
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (OvMap[i][j] == 2048)
            {
                return 1;
            }
            else if (OvMap[i][j] == 0)
            {
                return 0;
            }
        }
    }
    if ((PlusNum(OvMap,1) == 0))
    {
        return 2;
    }else{
        return 0;
    }
}

void Control(char input)
{
    if (input == 'w'){
        OprateWS(0);
    }else if (input== 's') {
         OprateWS(1);
    }else if (input == 'a') {
        OprateAD(0);
    }else if (input == 'd') {
        OprateAD(1);
    }else if (input == 'Q') {
        exit(0);
    }
}

int main()
{   
    char Answer;
    int isWin;
    MakeNum();
    while (1)
    {
        PrintMap();
        Control(PrintMenu());
        isWin = GameOver(Map);
        if (isWin != 0)
        {
            if (isWin == 1) 
            {
                printf("You Win!!!\n");
            }else
            {
                printf("You Lost!!!\n");
            }
            printf("Do you play again? Y/n \n");
            scanf(" %c",&Answer);
            if (toupper(Answer) == 'Y')
            {
                for (i = 0; i < 4; i++)
                {
                    for (j = 0; j < 4; j++)
                    {
                        Map[i][j] = 0;
                    }
                }
                main();
            }else{
                break;
            }
        }else {
            MakeNum();
            system("cls");
        }
    }
}
