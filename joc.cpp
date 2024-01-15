#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <sstream>
#include <string.h>

#include "joc.h"
#include "limbi.h"

#define BKG LIGHTGRAY

using namespace std;

bool sunet = true;

void deseneazaPiesa(TablaDeJoc TablaDeJoc, int linia, int coloana, int cul)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga=(getmaxx() - TablaDeJoc.height)/2;
    setcolor(BKG);
    setfillstyle(SOLID_FILL,BKG);
    x1=stanga+latura*coloana;
    y1=sus+latura*linia;
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(cul);
    setfillstyle(SOLID_FILL,cul);
    fillellipse(xmijloc,ymijloc,18,18);
}
void deseneazaTabla(TablaDeJoc TablaDeJoc,int jucator)
{
    int i,j;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga=(getmaxx() - TablaDeJoc.height)/2;
    int culoare;
    if(jucator == 1) culoare = BLUE;
    if(jucator == 2) culoare = RED;
    setbkcolor(BKG);
    clearviewport();
    setcolor(1);
    for (i = 0; i < TablaDeJoc.n; i++)
        for (j = 0; j < TablaDeJoc.n; j++)
            if (TablaDeJoc.loc[i][j] != tipLoc::invalid)
            {
                rectangle(stanga + latura * i,sus + latura * j,stanga + latura * (i+1),sus + latura * (j+1));
                if(TablaDeJoc.loc[i][j] == tipLoc::piesa) deseneazaPiesa(TablaDeJoc, i, j, culoare);
            }
}

bool isInsideButton(int x, int y, int left, int top, int right, int bottom)
{
    return (x >= left && x <= right && y >= top && y <= bottom);
}


bool mutarePiesa(TablaDeJoc &TablaDeJoc, int jucator)
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga= (getmaxx() - TablaDeJoc.height)/2;
    int click=false;
    int culoare, select;
    if(jucator == 1){
        culoare = BLUE;
        select = LIGHTBLUE;
    } else if(jucator == 2){
        culoare = RED;
        select = LIGHTRED;
    }
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            if(isInsideButton(mousex(),mousey(),750,550,800,600)){
                if(sunet == true){
                    PlaySound(NULL, NULL, 0);
                    readimagefile("sound-off.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
                    sunet = false;
                } else {
                    PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                    readimagefile("sound-on.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
                    sunet = true;
                }
            } else {
                click=true;
                x=mousex();
                y=mousey();
                linia1=(y-sus)/latura;
                coloana1=(x-stanga)/latura;
            }
        }
    while (!click);
    if(TablaDeJoc.loc[linia1][coloana1] == tipLoc::piesa)
    {
        deseneazaPiesa(TablaDeJoc,linia1,coloana1,select);
        click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            if(isInsideButton(mousex(),mousey(),750,550,800,600)){
                if(sunet == true){
                    PlaySound(NULL, NULL, 0);
                    readimagefile("sound-off.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
                    sunet = false;
                } else {
                    PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                    readimagefile("sound-on.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
                    sunet = true;
                }
            } else {
                click=true;
                x=mousex();
                y=mousey();
                linia2=(y-sus)/latura;
                coloana2=(x-stanga)/latura;
            }
        }
    while (!click);
        deseneazaPiesa(TablaDeJoc,linia1,coloana1, culoare);
        if(TablaDeJoc.loc[linia2][coloana2] == tipLoc::gol)
        {
            if(coloana1 == coloana2)
            {
                if(linia1 < TablaDeJoc.n-1){
                    if (linia1+2 == linia2 && TablaDeJoc.loc[linia1+1][coloana1] == tipLoc::piesa)
                    {
                        TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                        TablaDeJoc.loc[linia1+1][coloana1] = tipLoc::gol;
                        TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                        return true;
                    }
                }
                if(linia1 > 1){
                    if(linia1-2 == linia2 && TablaDeJoc.loc[linia1-1][coloana1] == tipLoc::piesa)
                    {
                        TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                        TablaDeJoc.loc[linia1-1][coloana1] = tipLoc::gol;
                        TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                        return true;
                    }
                }
            }
            else if(linia1 == linia2)
            {
                if(coloana1 < TablaDeJoc.n-1){
                    if(coloana1+2 == coloana2 && TablaDeJoc.loc[linia1][coloana1+1] == tipLoc::piesa)
                    {
                        TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                        TablaDeJoc.loc[linia1][coloana1+1] = tipLoc::gol;
                        TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                        return true;
                    }
                }
                if(coloana1 > 1){
                    if(coloana1-2 == coloana2 && TablaDeJoc.loc[linia1][coloana1-1] == tipLoc::piesa)
                    {
                        TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                        TablaDeJoc.loc[linia1][coloana1-1] = tipLoc::gol;
                        TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool mutariDisponibile(TablaDeJoc T){
    for(int i=0; i < T.n; i++){
        for(int j=0; j < T.n; j++){
            if(T.loc[i][j] == tipLoc::piesa){
                if(i < T.n-1){
                    if(T.loc[i+1][j] == tipLoc::piesa && T.loc[i+2][j] == tipLoc::gol) return true;
                }
                if(i > 1){
                    if(T.loc[i-1][j] == tipLoc::piesa && T.loc[i-2][j] == tipLoc::gol) return true;
                }
                if(j < T.n-1){
                    if(T.loc[i][j+1] == tipLoc::piesa && T.loc[i][j+2] == tipLoc::gol) return true;
                }
                if(j > 1){
                    if(T.loc[i][j-1] == tipLoc::piesa && T.loc[i][j-2] == tipLoc::gol) return true;
                }
            }
        }
    }
    return false;
}

bool castigat(TablaDeJoc T){
    for(int i=0; i<T.n; i++){
        for(int j=0; j<T.n; j++){
            if(T.loc[i][j] == piesa && i != T.n/2+1 || j != T.n/2+1) return false;
        }
    }
    return true;
}

void startJoc(TablaDeJoc T, int nr_jucatori, text& text) {
    clearviewport();
    bool ok;
    if(nr_jucatori == 1){
        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
        do
        {     
            deseneazaTabla(T,1);
            if(sunet == false){
                    readimagefile("sound-off.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
            } else {
                    readimagefile("sound-on.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
            }
            ok = mutarePiesa(T, 1);
            while(!ok) {ok = mutarePiesa(T, 1);}
        }
        while (mutariDisponibile(T));
        deseneazaTabla(T,1);
        if(sunet == false){
                readimagefile("sound-off.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
        } else {
                readimagefile("sound-on.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
        }
        if(castigat(T)){
            setcolor(GREEN);
            settextstyle(4,0,4);
            outtextxy((getmaxx()-textwidth(text.ai_castigat))/2, getmaxy()-textheight(text.ai_castigat), text.ai_castigat);
        } else {
            setcolor(RED);
            settextstyle(4,0,4);
            outtextxy((getmaxx()-textwidth(text.ai_castigat))/2, getmaxy()-textheight(text.ai_pierdut), text.ai_pierdut);
        }
        while(!ismouseclick(WM_LBUTTONDOWN));
    } else if(nr_jucatori == 2){
        int jucator_curent = 2;
        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
        do
        {
            if(jucator_curent == 1){
                jucator_curent = 2;
            }
            else if(jucator_curent == 2){
                jucator_curent = 1;
            }
            deseneazaTabla(T,jucator_curent);
            if(jucator_curent == 1){
                setcolor(BLUE);
                outtextxy((getmaxx()-textwidth(text.juc1))/2,20,text.juc1);
            } else if(jucator_curent == 2){
                setcolor(RED);
                outtextxy((getmaxx()-textwidth(text.juc2))/2,20,text.juc2);
            }
            if(sunet == false){
                    readimagefile("sound-off.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
            } else {
                    readimagefile("sound-on.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
            }
            ok = mutarePiesa(T, jucator_curent);
            while(!ok) {ok = mutarePiesa(T, jucator_curent);}
        }
        while (mutariDisponibile(T));
        deseneazaTabla(T,jucator_curent);
        if(jucator_curent == 1){
            setcolor(BLUE);
            outtextxy((getmaxx()-textwidth(text.juc1_castiga))/2, getmaxy()-textheight(text.juc1_castiga)-20,text.juc1_castiga);
        } else if(jucator_curent == 2){
            setcolor(RED);
            outtextxy((getmaxx()-textwidth(text.juc2_castiga))/2, getmaxy()-textheight(text.juc2_castiga)-20,text.juc2_castiga);
        }
        if(sunet == false){
                readimagefile("sound-off.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
        } else {
                readimagefile("sound-on.bmp", getmaxx()-50, getmaxy()-50, getmaxx(), getmaxy());
        }
        while(!ismouseclick(WM_LBUTTONDOWN));
    }
}