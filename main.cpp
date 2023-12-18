#include <iostream>
#include <winbgim.h>
#include <stdlib.h>

#define MAX 25
#define CUL 1
#define CUL_SEL 4
#define BKG 14

using namespace std;

enum tipLoc {
    invalid,
    gol,
    piesa
};

struct TablaDeJoc {
    tipLoc loc[MAX][MAX];
    int n;
    int width;
    int height;
};

void deseneazaPiesa(TablaDeJoc TablaDeJoc, int linia, int coloana, int cul)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga=(getmaxx() - TablaDeJoc.height)/2;
    setcolor(BKG); setfillstyle(SOLID_FILL,BKG);
    x1=stanga+latura*(coloana-1); y1=sus+latura*(linia-1);
    x2=x1+latura; y2=y1+latura;
    xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(cul); setfillstyle(SOLID_FILL,cul);
    fillellipse(xmijloc,ymijloc,18,18);
}

void desen(TablaDeJoc TablaDeJoc)
{
    int i,j;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga=(getmaxx() - TablaDeJoc.height)/2;
    setbkcolor(BKG);
    clearviewport();
    setcolor(1);
    for (i = 1; i <= TablaDeJoc.n; i++)
        for (j = 1; j <= TablaDeJoc.n; j++)
            if (TablaDeJoc.loc[i][j] != tipLoc::invalid){
                rectangle(stanga + latura * (i - 1),sus + latura * (j - 1),stanga + latura * i,sus + latura * j);
                if(TablaDeJoc.loc[i][j] == tipLoc::piesa) deseneazaPiesa(TablaDeJoc, i, j, CUL);
            }
}

void mutarePiesa(TablaDeJoc &TablaDeJoc, int  jucator)
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga=(getmaxx() - TablaDeJoc.height)/2;
    int click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(); y=mousey();
            linia1=(y-sus)/latura+1; coloana1=(x-stanga)/latura+1;
        }
    while (!click);
    if(TablaDeJoc.loc[linia1][coloana1] == tipLoc::piesa){
        deseneazaPiesa(TablaDeJoc,linia1,coloana1,CUL_SEL);
        click=false;
        do
            if(ismouseclick(WM_LBUTTONDOWN) && !click)
            {
                click=true;
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex(); y=mousey();
                linia2=(y-sus)/latura+1; coloana2=(x-stanga)/latura+1;
            }
        while (!click);
        deseneazaPiesa(TablaDeJoc,linia1,coloana1, CUL);
        if(TablaDeJoc.loc[linia2][coloana2] == tipLoc::gol){
            if(coloana1 == coloana2){
                if (linia1+2 == linia2 && TablaDeJoc.loc[linia1+1][coloana1] == tipLoc::piesa) {
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc ,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1+1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc ,linia1+1,coloana1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
                else if(linia1-2 == linia2 && TablaDeJoc.loc[linia1-1][coloana1] == tipLoc::piesa){
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1-1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1-1,coloana1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
            }
            else if(linia1 == linia2){
                if(coloana1+2 == coloana2 && TablaDeJoc.loc[linia1][coloana1+1] == tipLoc::piesa){
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1][coloana1+1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1,coloana1+1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
                else if(coloana1-2 == coloana2 && TablaDeJoc.loc[linia1][coloana1-1] == tipLoc::piesa){
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1][coloana1-1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1,coloana1-1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
            }
        }
    }
 }

bool castigat(int jucator)
{
    return false;
}

int main()
{
    TablaDeJoc T;
    T.n = 7;
    T.width = 400;
    T.height = 400;
    initwindow(800,600);
    for (int i=1; i<=T.n; i++)
    for (int j=1; j<=T.n; j++)
    {
        if(i != 4 || j != 4)
        {
            T.loc[i][j]=tipLoc::piesa;
        }
        else T.loc[i][j]=tipLoc::gol;
    }
    desen(T);
    do
    {
       mutarePiesa(T, 1);
    } while (!castigat(1) && !castigat(2));
   getch();
   closegraph();
   return 0;
}


