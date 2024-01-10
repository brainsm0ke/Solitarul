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
int scor;
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
            scor = 0;
}
void showMenu(int &startx1, int &starty1, int &startx2, int &starty2)
 {
    cleardevice();
    setbkcolor(MAGENTA);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = getmaxx();
    int windowHeight = getmaxy();

    int buttonWidth = 200;
    int buttonHeight = 100;
//butonul "incepe":
    startx1 = (windowWidth - buttonWidth) / 2;
    starty1 = (windowHeight - buttonHeight) / 2 - 60;
    startx2 = startx1 + buttonWidth + 100;
    starty2 = starty1 + buttonHeight + 100;

    //rectangle(startx1, starty1, startx2, starty2);
    outtextxy(startx1 + 70, starty1 + 15, "Start");
}
void showMenu2(int &onepx1, int &onepy1, int &onepx2, int &onepy2, int &twopx1, int &twopy1, int &twopx2, int &twopy2)
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
    onepy1 = (windowHeight - buttonHeight) / 2 - 60;
    onepx2 = onepx1 + buttonWidth;
    onepy2 = onepy1 + buttonHeight;
    outtextxy(onepx1 + 70, onepy1 + 15, "1 player");

     twopx1 = onepx1;
     twopy1 = onepy2 + buttonHeight + 40;
     twopx2 = twopx1 + buttonWidth;
     twopy2 = twopy1 + buttonHeight;
    outtextxy(twopx1 + 70, twopy1 + 15, "2 players");
}
bool isInsideButton(int x, int y, int left, int top, int right, int bottom) {
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
            x=mousex(); y=mousey();
            linia1=(y-sus)/latura+1; coloana1=(x-stanga)/latura+1;
        }
    while (!click);
    if(TablaDeJoc.loc[linia1][coloana1] == tipLoc::piesa){
        deseneazaPiesa(TablaDeJoc,linia1,coloana1,CUL_SEL);
            scor++;
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

void afisareScor()
{
  stringstream strs;
  strs << scor;
  string temp_str = strs.str();
  char* char_scor = (char*) temp_str.c_str();
    settextstyle(8, 0, 5);
      outtextxy(20, 10 ,char_scor);
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
    int startx1, starty1, startx2, starty2;
    int onepx1, onepy1, onepx2, onepy2, twopx1, twopy1, twopx2, twopy2;
    showMenu(startx1, starty1, startx2, starty2);
    bool running = true;
     TablaDeJoc T;
    T.n = 7;
    T.width = 400;
    T.height = 400;
    for (int i=1; i<=T.n; i++)
    for (int j=1; j<=T.n; j++)
    {
        if(i != 4 || j != 4)
        {
            T.loc[i][j]=tipLoc::piesa;
        }
        else T.loc[i][j]=tipLoc::gol;
    }
    while (running) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (isInsideButton(x, y, startx1, starty1, startx2, starty2)) {
                cleardevice();
                setbkcolor(YELLOW);
                clearviewport();
                showMenu2(onepx1, onepy1, onepx2, onepy2, twopx1, twopy1, twopx2, twopy2);
                bool running2 = true;
                 while (running2) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x2, y2;
            getmouseclick(WM_LBUTTONDOWN, x2, y2);

            if (isInsideButton(x2, y2, onepx1, onepy1, onepx2, onepy2)) {
                desen(T);
                PlaySound("Background.wav", NULL, SND_ASYNC | SND_NOSTOP);
                afisareScor();
    do
    {
       mutarePiesa(T, 1);
       afisareScor();
    } while (!castigat(1) && !castigat(2));
    cleardevice();
   setbkcolor(BKG);
    cleardevice();
    settextstyle(8, 0, 4);
    setcolor(1);
    outtextxy(70, 300, "Felicitari! Ai terminat jocul!");
            }
            else if (isInsideButton(x2, y2,twopx1, twopy1, twopx2, twopy2)) {
                running2 = false;
                break;
        }
    }
                 }
            }
        }
    }
   getch();
   closegraph();
}
