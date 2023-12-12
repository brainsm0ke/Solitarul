#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include<graphics.h>
#include<winbgim.h>
#define MAX 25
using namespace std;
int stanga,sus,width,height,latura,numar = 7,TablaDeJoc[MAX][MAX],culoare = 1;
bool gata;
void desen()
{
    int i,j;
    width = 400;
    height = 400;
    latura = width/numar;
    sus = (getmaxy() - width)/2;
    stanga=(getmaxx() - height)/2;
    setbkcolor(11);
    clearviewport();
    setcolor(1);
    for (i = 1; i <= numar; i++)
        for (j = 1; j <= numar; j++)
            rectangle(stanga + latura * (i - 1),sus + latura * (j - 1),stanga + latura * i,sus + latura * j);
}
void deseneazaPiesa(int linia, int coloana, int culoare)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    setcolor(11); setfillstyle(SOLID_FILL,11);
    x1=stanga+latura*(coloana-1); y1=sus+latura*(linia-1);
    x2=x1+latura; y2=y1+latura;
    xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(culoare); setfillstyle(SOLID_FILL,culoare);
    fillellipse(xmijloc,ymijloc,18,18);
}

void mutarePiesa(int jucator)
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
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
    TablaDeJoc[linia1][coloana1]=0;
    TablaDeJoc[linia2][coloana2]=jucator;
    if (linia1==linia2)
        {
            TablaDeJoc[linia1][(coloana1+coloana2)/2]=0;
            deseneazaPiesa(linia1,(coloana1+coloana2)/2,11);
        }
    else
        {
            TablaDeJoc[(linia1+linia2)/2][coloana1]=0;
            deseneazaPiesa((linia1+linia2)/2,coloana1,11);
        }
    deseneazaPiesa(linia1,coloana1,11);
    deseneazaPiesa(linia2,coloana2,culoare);
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

        if(i != 4 || j != 4)
        {
            TablaDeJoc[i][j]=1;
             deseneazaPiesa(i,j, culoare);
        }
        else
            TablaDeJoc[i][j]=0;
     }
    do
    {
       mutarePiesa(1);
    } while (!castigat(1) && !castigat(2));
   getch();
   closegraph();
   return 0;
}
