#include <iostream>
#include <winbgim.h>
#include <stdlib.h>

#define MAX 25
using namespace std;

enum tipLoc {
    invalid,
    gol,
    piesa
};

int stanga,sus,width,height,latura,numar = 7, cul=1, sel=4;
tipLoc TablaDeJoc[MAX][MAX];
bool gata;
void desen()
{
    int i,j;
    width = 400;
    height = 400;
    latura = width/numar;
    sus = (getmaxy() - width)/2;
    stanga=(getmaxx() - height)/2;
    setbkcolor(15);
    clearviewport();
    setcolor(1);
    for (i = 1; i <= numar; i++)
        for (j = 1; j <= numar; j++)
            rectangle(stanga + latura * (i - 1),sus + latura * (j - 1),stanga + latura * i,sus + latura * j);
}
void deseneazaPiesa(int linia, int coloana, int cul)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    setcolor(15); setfillstyle(SOLID_FILL,15);
    x1=stanga+latura*(coloana-1); y1=sus+latura*(linia-1);
    x2=x1+latura; y2=y1+latura;
    xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(cul); setfillstyle(SOLID_FILL,cul);
    fillellipse(xmijloc,ymijloc,18,18);
}

void mutarePiesa(int jucator)
{
    int linia1,coloana1,linia2,coloana2,x,y;
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
    if(TablaDeJoc[linia1][coloana1] == tipLoc::piesa){
        deseneazaPiesa(linia1,coloana1,sel);
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
        deseneazaPiesa(linia1,coloana1, cul);
        if(TablaDeJoc[linia2][coloana2] == tipLoc::gol){
            if(coloana1 == coloana2){
                if (linia1+2 == linia2 && TablaDeJoc[linia1+1][coloana1] == tipLoc::piesa) {
                    TablaDeJoc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(linia1, coloana1, 15);
                    TablaDeJoc[linia1+1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(linia1+1,coloana1, 15);
                    TablaDeJoc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(linia2, coloana2, cul);
                }
                else if(linia1-2 == linia2 && TablaDeJoc[linia1-1][coloana1] == tipLoc::piesa){
                    TablaDeJoc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(linia1, coloana1, 15);
                    TablaDeJoc[linia1-1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(linia1-1,coloana1, 15);
                    TablaDeJoc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(linia2, coloana2, cul);
                }
            }
            else if(linia1 == linia2){
                if(coloana1+2 == coloana2 && TablaDeJoc[linia1][coloana1+1] == tipLoc::piesa){
                    TablaDeJoc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(linia1, coloana1, 15);
                    TablaDeJoc[linia1][coloana1+1] = tipLoc::gol;
                    deseneazaPiesa(linia1,coloana1+1, 15);
                    TablaDeJoc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(linia2, coloana2, cul);
                }
                else if(coloana1-2 == coloana2 && TablaDeJoc[linia1][coloana1-1] == tipLoc::piesa){
                    TablaDeJoc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(linia1, coloana1, 15);
                    TablaDeJoc[linia1][coloana1-1] = tipLoc::gol;
                    deseneazaPiesa(linia1,coloana1-1, 15);
                    TablaDeJoc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(linia2, coloana2, cul);
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
    int i,j;
   initwindow(800,600);
   desen();
    for (i=1; i<=numar; i++)
    for (j=1; j<=numar; j++)
    {
        if(i != numar/2+1 || j != numar/2+1)
        {
            TablaDeJoc[i][j]=tipLoc::piesa;
            deseneazaPiesa(i,j, cul);
        }
        else TablaDeJoc[i][j]=tipLoc::gol;
    }
    do
    {
       mutarePiesa(1);
    } while (!castigat(1) && !castigat(2));
   getch();
   closegraph();
   return 0;
}


