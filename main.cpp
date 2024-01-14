#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <windows.h>
#include<mmsystem.h>
#include <sstream>
#include <string.h>

#define MAX 25
#define CUL 1
#define CUL_SEL 4
#define BKG 14

using namespace std;

enum tipLoc
{
    invalid,
    gol,
    piesa
};

struct TablaDeJoc
{
    tipLoc loc[MAX][MAX];
    int n;
    int width;
    int height;
};
int scor;
void deseneazaPiesa(TablaDeJoc TablaDeJoc, int linia, int coloana, int cul)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    int latura = TablaDeJoc.width/TablaDeJoc.n;
    int sus = (getmaxy() - TablaDeJoc.width)/2;
    int stanga=(getmaxx() - TablaDeJoc.height)/2;
    setcolor(BKG);
    setfillstyle(SOLID_FILL,BKG);
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(cul);
    setfillstyle(SOLID_FILL,cul);
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
            if (TablaDeJoc.loc[i][j] != tipLoc::invalid)
            {
                rectangle(stanga + latura * (i - 1),sus + latura * (j - 1),stanga + latura * i,sus + latura * j);
                if(TablaDeJoc.loc[i][j] == tipLoc::piesa) deseneazaPiesa(TablaDeJoc, i, j, CUL);
            }
    scor = 0;
}
void showMenu(int &startx1, int &starty1, int &startx2, int &starty2, int &rulesx1, int &rulesy1, int &rulesx2, int &rulesy2)
{
    cleardevice();
    setbkcolor(MAGENTA);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    int buttonWidth = 200;
    int buttonHeight = 100;

    rulesx1 = 10;
    rulesy1 = 10;
    rulesx2 = rulesx1 + buttonWidth + 100;
    rulesy2 = rulesy1 + buttonHeight + 100;
    outtextxy(rulesx1 + 70, rulesy1 + 15, "How to play");


    startx1 = (windowWidth - buttonWidth) / 2 - 50;
    starty1 = (windowHeight - buttonHeight) / 2 - 20;
    startx2 = startx1 + buttonWidth + 100;
    starty2 = starty1 + buttonHeight + 100;

    //rectangle(startx1, starty1, startx2, starty2);
    outtextxy(startx1 + 70, starty1 + 15, "Start");
}
void showMenu2(int &engx1, int &engy1, int &engx2, int &engy2, int &rox1, int &roy1, int &rox2, int &roy2)
{
    cleardevice();
    setbkcolor(MAGENTA);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    int buttonWidth = 200;
    int buttonHeight = 50;

    engx1 = (windowWidth - buttonWidth) / 4 + 80;
    engy1 = (windowHeight - buttonHeight) / 2 - 100;
    engx2 = engx1 + buttonWidth;
    engy2 = engy1 + buttonHeight;
    outtextxy(engx1 + 70, engy1 + 15, "English");

    rox1 = engx1;
    roy1 = engy2 + buttonHeight + 40;
    rox2 = rox1 + buttonWidth;
    roy2 = roy1 + buttonHeight;
    outtextxy(rox1 + 70, roy1 + 15, "Romanian");
}
void showMenu3(int &onepx1, int &onepy1, int &onepx2, int &onepy2, int &twopx1, int &twopy1, int &twopx2, int &twopy2)
{
    cleardevice();
    setbkcolor(MAGENTA);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    int buttonWidth = 200;
    int buttonHeight = 50;

    onepx1 = (windowWidth - buttonWidth) / 4 + 50;
    onepy1 = (windowHeight - buttonHeight) / 2 - 100;
    onepx2 = onepx1 + buttonWidth;
    onepy2 = onepy1 + buttonHeight;
    outtextxy(onepx1 + 70, onepy1 + 15, "1 player");

    twopx1 = onepx1;
    twopy1 = onepy2 + buttonHeight + 40;
    twopx2 = twopx1 + buttonWidth;
    twopy2 = twopy1 + buttonHeight;
    outtextxy(twopx1 + 70, twopy1 + 15, "2 players");
}
void showMenu4(int &t1x1, int &t1y1, int &t1x2, int &t1y2, int &t2x1, int &t2y1, int &t2x2, int &t2y2, int &t3x1, int &t3y1, int &t3x2, int &t3y2)
{
    cleardevice();
    setbkcolor(MAGENTA);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    int buttonWidth = 200;
    int buttonHeight = 50;

    t1x1 = (windowWidth - buttonWidth) / 3 + 40;
    t1y1 = (windowHeight - buttonHeight) / 2 - 130;
    t1x2 = t1x1 + buttonWidth;
    t1y2 = t1y1 + buttonHeight;
    outtextxy(t1x1 + 70, t1y1 + 15, "Tabla 1");

    t2x1 = t1x1;
    t2y1 = t1y2 + 50;
    t2x2 = t2x1 + buttonWidth;
    t2y2 = t2y1 + buttonHeight;
    outtextxy(t2x1 + 70, t2y1 + 15, "Tabla 2");

    t3x1 = t2x1;
    t3y1 = t2y2 + 50;
    t3x2 = t3x1 + buttonWidth;
    t3y2 = t3y1 + buttonHeight;
    outtextxy(t3x1 + 70, t3y1 + 15, "Tabla 3");
}
bool isInsideButton(int x, int y, int left, int top, int right, int bottom)
{
    return (x >= left && x <= right && y >= top && y <= bottom);
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
            x=mousex();
            y=mousey();
            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
        }
    while (!click);
    if(TablaDeJoc.loc[linia1][coloana1] == tipLoc::piesa)
    {
        deseneazaPiesa(TablaDeJoc,linia1,coloana1,CUL_SEL);
        click=false;
        do
            if(ismouseclick(WM_LBUTTONDOWN) && !click)
            {
                click=true;
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                linia2=(y-sus)/latura+1;
                coloana2=(x-stanga)/latura+1;
            }
        while (!click);
        deseneazaPiesa(TablaDeJoc,linia1,coloana1, CUL);
        if(TablaDeJoc.loc[linia2][coloana2] == tipLoc::gol)
        {
            if(coloana1 == coloana2)
            {
                if (linia1+2 == linia2 && TablaDeJoc.loc[linia1+1][coloana1] == tipLoc::piesa)
                {
                    scor++;
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1+1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1+1,coloana1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
                else if(linia1-2 == linia2 && TablaDeJoc.loc[linia1-1][coloana1] == tipLoc::piesa)
                {
                    scor++;
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1-1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1-1,coloana1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
            }
            else if(linia1 == linia2)
            {
                if(coloana1+2 == coloana2 && TablaDeJoc.loc[linia1][coloana1+1] == tipLoc::piesa)
                {
                    scor++;
                    TablaDeJoc.loc[linia1][coloana1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1, coloana1, BKG);
                    TablaDeJoc.loc[linia1][coloana1+1] = tipLoc::gol;
                    deseneazaPiesa(TablaDeJoc,linia1,coloana1+1, BKG);
                    TablaDeJoc.loc[linia2][coloana2] = tipLoc::piesa;
                    deseneazaPiesa(TablaDeJoc,linia2, coloana2, CUL);
                }
                else if(coloana1-2 == coloana2 && TablaDeJoc.loc[linia1][coloana1-1] == tipLoc::piesa)
                {
                    scor++;
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

void afisareScor()
{
    stringstream strs;
    strs << scor;
    string temp_str = strs.str();
    char* char_scor = (char*) temp_str.c_str();
    settextstyle(8, 0, 5);
    outtextxy(20, 10,char_scor);
}

bool castigat(int jucator)
{
    return false;
}

int main()
{
    initwindow(800,600,"Solitar");
    setbkcolor(YELLOW);
    clearviewport();
    int startx1, starty1, startx2, starty2, rulesx1, rulesy1, rulesx2, rulesy2;
    int engx1, engy1, engx2, engy2, rox1, roy1, rox2, roy2;
    int onepx1, onepy1, onepx2, onepy2, twopx1, twopy1, twopx2, twopy2;
    int t1x1, t1y1, t1x2, t1y2, t2x1, t2y1, t2x2, t2y2, t3x1, t3y1, t3x2, t3y2;
    showMenu(startx1, starty1, startx2, starty2, rulesx1, rulesy1, rulesx2, rulesy2);
    bool running = true;
    TablaDeJoc T;
    T.n = 7;
    T.width = 400;
    T.height = 400;
    while (running)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (isInsideButton(x, y, startx1, starty1, startx2, starty2))
            {
                cleardevice();
                setbkcolor(YELLOW);
                clearviewport();
                showMenu3(onepx1, onepy1, onepx2, onepy2, twopx1, twopy1, twopx2, twopy2);
                bool running3 = true;
                while (running3)
                {
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x3, y3;
                        getmouseclick(WM_LBUTTONDOWN, x3, y3);

                        if (isInsideButton(x3, y3, onepx1, onepy1, onepx2, onepy2))
                        {
                            cleardevice();
                            setbkcolor(YELLOW);
                            clearviewport();
                            showMenu4(t1x1, t1y1, t1x2, t1y2, t2x1, t2y1, t2x2, t2y2, t3x1, t3y1, t3x2, t3y2);
                            bool running4 = true;
                            while (running4)
                            {
                                if (ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int x4, y4;
                                    getmouseclick(WM_LBUTTONDOWN, x4, y4);

                                    if (isInsideButton(x4, y4, t1x1, t1y1, t1x2, t1y2))
                                    {
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
                                        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                                        afisareScor();
                                        do
                                        {
                                            mutarePiesa(T, 1);
                                            //PlaySound("MutarePiesa.wav", NULL, SND_ASYNC);
                                            afisareScor();
                                        }
                                        while (!castigat(1) && !castigat(2));
                                        cleardevice();
                                        setbkcolor(BKG);
                                        cleardevice();
                                        settextstyle(8, 0, 4);
                                        setcolor(1);
                                        outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
                                    }
                                    if (isInsideButton(x4, y4, t2x1, t2y1, t2x2, t2y2))
                                    {
                                        for (int i=1; i<=T.n; i++)
                                            for (int j=1; j<=T.n; j++)
                                            {
                                                if(i != 4 || j != 4)
                                                {
                                                    T.loc[i][j]=tipLoc::piesa;
                                                }
                                                else T.loc[i][j]=tipLoc::gol;
                                                T.loc[1][1]=tipLoc::invalid;
                                                //T.loc[1][1]=tipLoc::invalid;
                                                T.loc[1][2]=tipLoc::invalid;
                                                T.loc[1][6]=tipLoc::invalid;
                                                T.loc[1][7]=tipLoc::invalid;
                                                //T.loc[2][1]=tipLoc::gol;
                                                T.loc[2][1]=tipLoc::invalid;
                                                T.loc[2][7]=tipLoc::invalid;
                                                T.loc[6][1]=tipLoc::invalid;
                                                T.loc[6][7]=tipLoc::invalid;
                                                T.loc[7][1]=tipLoc::invalid;
                                                T.loc[7][1]=tipLoc::invalid;
                                                T.loc[7][2]=tipLoc::invalid;
                                                T.loc[7][6]=tipLoc::invalid;
                                                T.loc[7][7]=tipLoc::invalid;
                                            }
                                        desen(T);
                                        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                                        afisareScor();
                                        do
                                        {
                                            mutarePiesa(T, 1);
                                            //PlaySound("MutarePiesa.wav", NULL, SND_ASYNC);
                                            afisareScor();
                                        }
                                        while (!castigat(1) && !castigat(2));
                                        cleardevice();
                                        setbkcolor(BKG);
                                        cleardevice();
                                        settextstyle(8, 0, 4);
                                        setcolor(1);
                                        outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
                                    }
                                    else if (isInsideButton(x4, y4, t3x1, t3y1, t3x2, t3y2))
                                    {
                                        for (int i=1; i<=T.n; i++)
                                            for (int j=1; j<=T.n; j++)
                                            {
                                                if(i != 4 || j != 4)
                                                {
                                                    T.loc[i][j]=tipLoc::piesa;
                                                }
                                                else T.loc[i][j]=tipLoc::gol;
                                                T.loc[1][1]=tipLoc::invalid;
                                                T.loc[1][2]=tipLoc::invalid;
                                                T.loc[1][6]=tipLoc::invalid;
                                                T.loc[1][7]=tipLoc::invalid;
                                                T.loc[2][1]=tipLoc::invalid;
                                                T.loc[2][2]=tipLoc::invalid;
                                                T.loc[2][6]=tipLoc::invalid;
                                                T.loc[2][7]=tipLoc::invalid;
                                                T.loc[6][1]=tipLoc::invalid;
                                                T.loc[6][7]=tipLoc::invalid;
                                                T.loc[6][2]=tipLoc::invalid;
                                                T.loc[6][6]=tipLoc::invalid;
                                                T.loc[7][1]=tipLoc::invalid;
                                                T.loc[7][2]=tipLoc::invalid;
                                                T.loc[7][6]=tipLoc::invalid;
                                                T.loc[7][7]=tipLoc::invalid;
                                            }
                                        desen(T);
                                        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                                        afisareScor();
                                        do
                                        {
                                            mutarePiesa(T, 1);
                                            //PlaySound("MutarePiesa.wav", NULL, SND_ASYNC);
                                            afisareScor();
                                        }
                                        while (!castigat(1) && !castigat(2));
                                        cleardevice();
                                        setbkcolor(BKG);
                                        cleardevice();
                                        settextstyle(8, 0, 4);
                                        setcolor(1);
                                        outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
                                    }
                                }
                            }
                        }
                        else
                            if (isInsideButton(x3, y3, twopx1, twopy1, twopx2, twopy2))
                        {
                            cleardevice();
                            setbkcolor(YELLOW);
                            clearviewport();
                            showMenu4(t1x1, t1y1, t1x2, t1y2, t2x1, t2y1, t2x2, t2y2, t3x1, t3y1, t3x2, t3y2);
                            bool running4 = true;
                            while (running4)
                            {
                                if (ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int x4, y4;
                                    getmouseclick(WM_LBUTTONDOWN, x4, y4);

                                    if (isInsideButton(x4, y4, t1x1, t1y1, t1x2, t1y2))
                                    {
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
                                        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                                        afisareScor();
                                        do
                                        {
                                            mutarePiesa(T, 1);
                                            //PlaySound("MutarePiesa.wav", NULL, SND_ASYNC);
                                            afisareScor();
                                        }
                                        while (!castigat(1) && !castigat(2));
                                        cleardevice();
                                        setbkcolor(BKG);
                                        cleardevice();
                                        settextstyle(8, 0, 4);
                                        setcolor(1);
                                        outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
                                    }
                                    if (isInsideButton(x4, y4, t2x1, t2y1, t2x2, t2y2))
                                    {
                                        for (int i=1; i<=T.n; i++)
                                            for (int j=1; j<=T.n; j++)
                                            {
                                                if(i != 4 || j != 4)
                                                {
                                                    T.loc[i][j]=tipLoc::piesa;
                                                }
                                                else T.loc[i][j]=tipLoc::gol;
                                                T.loc[1][1]=tipLoc::invalid;
                                                //T.loc[1][1]=tipLoc::invalid;
                                                T.loc[1][2]=tipLoc::invalid;
                                                T.loc[1][6]=tipLoc::invalid;
                                                T.loc[1][7]=tipLoc::invalid;
                                                //T.loc[2][1]=tipLoc::gol;
                                                T.loc[2][1]=tipLoc::invalid;
                                                T.loc[2][7]=tipLoc::invalid;
                                                T.loc[6][1]=tipLoc::invalid;
                                                T.loc[6][7]=tipLoc::invalid;
                                                T.loc[7][1]=tipLoc::invalid;
                                                T.loc[7][1]=tipLoc::invalid;
                                                T.loc[7][2]=tipLoc::invalid;
                                                T.loc[7][6]=tipLoc::invalid;
                                                T.loc[7][7]=tipLoc::invalid;
                                            }
                                        desen(T);
                                        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                                        afisareScor();
                                        do
                                        {
                                            mutarePiesa(T, 1);
                                            //PlaySound("MutarePiesa.wav", NULL, SND_ASYNC);
                                            afisareScor();
                                        }
                                        while (!castigat(1) && !castigat(2));
                                        cleardevice();
                                        setbkcolor(BKG);
                                        cleardevice();
                                        settextstyle(8, 0, 4);
                                        setcolor(1);
                                        outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
                                    }
                                    else if (isInsideButton(x4, y4, t3x1, t3y1, t3x2, t3y2))
                                    {
                                        for (int i=1; i<=T.n; i++)
                                            for (int j=1; j<=T.n; j++)
                                            {
                                                if(i != 4 || j != 4)
                                                {
                                                    T.loc[i][j]=tipLoc::piesa;
                                                }
                                                else T.loc[i][j]=tipLoc::gol;
                                                T.loc[1][1]=tipLoc::invalid;
                                                T.loc[1][2]=tipLoc::invalid;
                                                T.loc[1][6]=tipLoc::invalid;
                                                T.loc[1][7]=tipLoc::invalid;
                                                T.loc[2][1]=tipLoc::invalid;
                                                T.loc[2][2]=tipLoc::invalid;
                                                T.loc[2][6]=tipLoc::invalid;
                                                T.loc[2][7]=tipLoc::invalid;
                                                T.loc[6][1]=tipLoc::invalid;
                                                T.loc[6][7]=tipLoc::invalid;
                                                T.loc[6][2]=tipLoc::invalid;
                                                T.loc[6][6]=tipLoc::invalid;
                                                T.loc[7][1]=tipLoc::invalid;
                                                T.loc[7][2]=tipLoc::invalid;
                                                T.loc[7][6]=tipLoc::invalid;
                                                T.loc[7][7]=tipLoc::invalid;
                                            }
                                        desen(T);
                                        PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                                        afisareScor();
                                        do
                                        {
                                            mutarePiesa(T, 1);
                                            //PlaySound("MutarePiesa.wav", NULL, SND_ASYNC);
                                            afisareScor();
                                        }
                                        while (!castigat(1) && !castigat(2));
                                        cleardevice();
                                        setbkcolor(BKG);
                                        cleardevice();
                                        settextstyle(8, 0, 4);
                                        setcolor(1);
                                        outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
                                    }
                                }
                            }
                        }
                    }
                }
            }
                        else
                        {
                            if (isInsideButton(x, y, rulesx1, rulesy1, rulesx2, rulesy2))
                            {
                                cleardevice();
                                setbkcolor(YELLOW);
                                clearviewport();
                                showMenu2(engx1, engy1, engx2, engy2, rox1, roy1, rox2, roy2);
                                bool running2 = true;
                                while (running2)
                                {
                                    if (ismouseclick(WM_LBUTTONDOWN))
                                    {
                                        int x2, y2;
                                        getmouseclick(WM_LBUTTONDOWN, x2, y2);

                                        if (isInsideButton(x2, y2, rox1, roy1, rox2, roy2))
                                        {
                                            cleardevice();
                                            setbkcolor(YELLOW);
                                            clearviewport();
                                            char *rules1 = "Un pion poate fi mutat doar peste un pion vecin, orizontal sau ";
                                            char *rules2 = "vertical (nu si diagonal) cu conditia ca in spatele acestuia sa ";
                                            char *rules3 = "existe o casuta libera. Pionul peste care se sare este eliminat.";
                                            char *rules4 = "Prin mutari adecvate, trebuie ca toti pionii sa fie eliminati, ";
                                            char *rules5 = "mai putin unul care trebuie sa ajunga in final fix in centrul ";
                                            char *rules6 = "tablei de joc.";
                                            char *rules7 = "In conditiile in care sunt 2 jucatori, castiga cel care face ";
                                            char *rules8 = "ultima mutare(chiar daca nu s-a indeplinit conditia de castig ";
                                            char *rules9 = "de mai sus).";
                                            settextstyle(8, 0, 2);
                                            outtextxy(30, 50, rules1);
                                            outtextxy(10, 90, rules2);
                                            outtextxy(10, 130, rules3);
                                            outtextxy(10, 170, rules4);
                                            outtextxy(10, 210, rules5);
                                            outtextxy(10, 250, rules6);
                                            outtextxy(30, 290, rules7);
                                            outtextxy(10, 330, rules8);
                                            outtextxy(10, 370, rules9);

                                        }
                                        if (isInsideButton(x2, y2, engx1, engy1, engx2, engy2))
                                        {
                                            cleardevice();
                                            setbkcolor(YELLOW);
                                            clearviewport();
                                            char *rules1 = "A pawn can only be moved over a neighboring pawn, horizontally ";
                                            char *rules2 = "or vertically (not diagonally), provided that there is a free ";
                                            char *rules3 = "square behind it. The jumped pawn is removed. By appropriate ";
                                            char *rules4 = "moves, all pawns must be eliminated, except for one that must ";
                                            char *rules5 = "end up in the center of the game board.";
                                            char *rules6 = "In the conditions where there are 2 players, the one who makes ";
                                            char *rules7 = "the last move wins (even if the winning condition above has not ";
                                            char *rules8 = "been met).";
                                            settextstyle(8, 0, 2);
                                            outtextxy(30, 50, rules1);
                                            outtextxy(10, 90, rules2);
                                            outtextxy(10, 130, rules3);
                                            outtextxy(10, 170, rules4);
                                            outtextxy(10, 210, rules5);
                                            outtextxy(30, 250, rules6);
                                            outtextxy(10, 290, rules7);
                                            outtextxy(10, 330, rules8);

                                        }
                                    }
                                }
                            }
                        }
                    }
    }
                getch();
                closegraph();
}
