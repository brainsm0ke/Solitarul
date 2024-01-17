#include <iostream>
#include <winbgim.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <commdlg.h>
#include <winuser.h>
#include <mmsystem.h>
#include <sstream>
#include <string.h>
#include <fstream>

struct text {
    char* un_jucator;
    char* doi_jucatori;
    char* reguli;
    char* alege_un_alt_tabel;
    char* juc1;
    char* juc2;
    char* ai_castigat;
    char* ai_pierdut;
    char* juc1_castiga;
    char* juc2_castiga;
    char* descriere_reguli;
    char* inapoi;
};

enum tipLoc
{
    invalid,
    gol,
    piesa
};

struct TablaDeJoc
{
    tipLoc loc[25][25];
    int n;
    int width;
    int height;
};

text Romana = {
    "Un jucator",
    "Doi Jucatori",
    "Reguli de joc",
    "Alege un alt tabel",
    "Jucator 1",
    "Jucator 2",
    "Ai castigat!",
    "Ai pierdut!",
    "Jucatorul 1 castiga!",
    "Jucatorul 2 castiga!",
    "Un pion poate fi mutat doar peste un pion vecin, orizontal sau\n"
    "vertical (nu si diagonal) cu conditia ca in spatele acestuia sa\n"
    "existe o casuta libera. Pionul peste care se sare este eliminat.\n"
    "Prin mutari adecvate, trebuie ca toti pionii sa fie eliminati,\n"
    "mai putin unul care trebuie sa ajunga in final fix in centrul\n"
    "tablei de joc.\n"
    "In conditiile in care sunt 2 jucatori, castiga cel care face\n"
    "ultima mutare (chiar daca nu s-a indeplinit conditia de castig\n"
    "de mai sus).",
    "Inapoi"
};

text Engleza = {
    "One player",
    "Two players",
    "Game rules",
    "Choose another table",
    "Player 1",
    "Player 2",
    "You win!",
    "You lose!",
    "Player 1 wins!",
    "Player 2 wins!",
    "A pawn can only be moved over a neighboring pawn, horizontally\n"
    "or vertically (not diagonally), provided that there is a free\n"
    "square behind it. The jumped pawn is removed. By appropriate\n"
    "moves, all pawns must be eliminated, except for one that must\n"
    "end up in the center of the game board.\n"
    "In the conditions where there are 2 players, the one who makes\n"
    "the last move wins (even if the winning condition above has not\n"
    "been met).\n",
    "Back"
};

bool isInsideButton(int x, int y, int left, int top, int right, int bottom)
{
    return (x >= left && x <= right && y >= top && y <= bottom);
}

void ReguliJoc(text& text) {
    int x=20,y=20;
    setbkcolor(LIGHTGRAY);
    clearviewport();
    settextstyle(3,0,3);
    setcolor(BLACK);
    std::string str(text.descriere_reguli);
    char* pch = strtok((char*)str.c_str(),"\n");
    while(pch != NULL){
        outtextxy(x,y,pch);
        y += textheight("A");
        pch = strtok(NULL, "\n");
    }
    x = 20;
    y = getmaxy()-20-textheight("A");
    bool ok = 0;
    settextstyle(4,0,3);
    setbkcolor(WHITE);
    outtextxy(x,y, text.inapoi);
    while(!ok){
        while(!ismouseclick(WM_LBUTTONDOWN));
        clearmouseclick(WM_LBUTTONDOWN);
        if(isInsideButton(mousex(),mousey(),x,y,x+textwidth(text.inapoi), y+textheight(text.inapoi))){
            ok = 1;
        }
    }

}

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

TablaDeJoc IncarcaTabla(char* path){
    TablaDeJoc T;
    T.height = 400;
    T.width = 400;
    std::ifstream file(path);
    if(file.is_open()){
        file >> T.n;
        char c;
        for(int i=0;i < T.n; i++){
            for(int j=0;j < T.n; j++){
                file.get(c);
                while(c == '\n') file.get(c);
                if(c == '_') T.loc[i][j] = tipLoc::invalid;
                else if(c == 'o') T.loc[i][j] = tipLoc::gol;
                else if(c == '.') T.loc[i][j] = tipLoc::piesa;
            }
        }
    } else throw 0;
    return T;
}

void SelectareFisierTabla(char* c, text& text) {
    OPENFILENAMEA ofn;
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = GetFocus();
    ofn.lpstrFilter = "Text file (*.txt)\0*.txt\0\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.lpstrFile = c;
    ofn.nFilterIndex = 0;
    ofn.nMaxFile = 100;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrTitle = text.alege_un_alt_tabel;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if(!GetOpenFileNameA(&ofn)){
        c[0] = '\0';
    }
}

int main() {
    char c[100];
    initwindow(800,600,"Solitar");
    setbkcolor(LIGHTGRAY);
    clearviewport();
    int x_padding, y_padding;
    text text;
    int nr_jucatori;
    bool ok = false;
    int x1,y1,x2,y2,x3,y3,x4,y4;
    x1 = (getmaxx()-550)/2;
    y1 = (getmaxy()-150)/2;
    x2 = x1 + 300;
    y2 = y1;
    readimagefile("RO.bmp", x1, y1, x1+250, y1+150);
    readimagefile("EN.bmp", x2, y2, x2+250, y2+150);
    while(!ok){
        while(!ismouseclick(WM_LBUTTONDOWN));
        clearmouseclick(WM_LBUTTONDOWN);
        if(isInsideButton(mousex(), mousey(), 
        (getmaxx()-550)/2, (getmaxy()-150)/2, 
        (getmaxx()-550)/2+250, (getmaxy()-150)/2+150)){
            text = Romana;
            ok = true;
        }
        else if(isInsideButton(mousex(), mousey(), 
        (getmaxx()-550)/2+300, (getmaxy()-150)/2, 
        (getmaxx()-550)/2+550, (getmaxy()-150)/2+150)){
            text = Engleza;
            ok = true;
        }
    }

    settextstyle(4,0,4);
    x1 = (getmaxx()-textwidth(text.un_jucator)-textwidth(text.doi_jucatori)-30)/2;
    y1 = (getmaxy()-textheight(text.un_jucator))/2;
    x2 = x1 + 30 + textwidth(text.doi_jucatori);
    y2 = y1;
    x3 = (getmaxx()-textwidth(text.reguli))/2;
    y3 = getmaxy()-textheight(text.reguli)-20;
    ok=false;
    while(!ok){
        settextstyle(4,0,4);
        setbkcolor(LIGHTGRAY);
        clearviewport();
        setbkcolor(WHITE);
        setcolor(BLACK);
        outtextxy(x1, y1, text.un_jucator);
        outtextxy(x2, y2, text.doi_jucatori);
        outtextxy(x3,y3, text.reguli);
        while(!ismouseclick(WM_LBUTTONDOWN));
        clearmouseclick(WM_LBUTTONDOWN);
        if(isInsideButton(mousex(),mousey(),x1,y1,x1+textwidth(text.un_jucator),y1+textheight(text.un_jucator))){
            nr_jucatori = 1;
            ok = true;
        } else if(isInsideButton(mousex(),mousey(),x2,y2,x2+textwidth(text.doi_jucatori),y2+textheight(text.doi_jucatori))){
            nr_jucatori = 2;
            ok = true;
        } else if(isInsideButton(mousex(),mousey(),x3,y3,x3+textwidth(text.reguli), y3+textheight(text.reguli))){{
            ReguliJoc(text);
        }
        }
    }
    setbkcolor(LIGHTGRAY);

    settextstyle(4,0,4);
    x1 = (getmaxx()-200*3-60)/2;
    y1 = (getmaxy()-200)/2;
    x2 = x1 + 220;
    y2 = y1;
    x3 = x2 + 220;
    y3 = y2;
    x4 = (getmaxx()-textwidth(text.alege_un_alt_tabel))/2;
    y4 = getmaxy()-textheight(text.alege_un_alt_tabel)-20;
    ok = false;
    while(!ok){
        setbkcolor(LIGHTGRAY);
        clearviewport();
        setcolor(BLACK);
        setbkcolor(WHITE);
        outtextxy(x4,y4,text.alege_un_alt_tabel);
        settextstyle(4,0,4);
        readimagefile("Tabla1.jpg", x1,y1,x1+200,y1+200);
        readimagefile("Tabla2.jpg", x2,y2,x2+200, y2+200);
        readimagefile("Tabla3.jpg", x3,y3,x3+200,y3+200);
        while(!ismouseclick(WM_LBUTTONDOWN));
        clearmouseclick(WM_LBUTTONDOWN);
        if(isInsideButton(mousex(),mousey(),x1,y1,x1+200,y1+200)){
            startJoc(IncarcaTabla("Tabla1.txt"), nr_jucatori, text);
            ok = true;
        } else if(isInsideButton(mousex(),mousey(),x2,y2,x2+200,y2+200)){
            startJoc(IncarcaTabla("Tabla2.txt"), nr_jucatori, text);
            ok = true;
        } else if(isInsideButton(mousex(),mousey(),x3,y3,x3+200,y3+200)){
            startJoc(IncarcaTabla("Tabla3.txt"), nr_jucatori, text);
            ok = true;
        } else if(isInsideButton(mousex(),mousey(),x4,y4,
        x4+textwidth(text.alege_un_alt_tabel), y4+textheight(text.alege_un_alt_tabel))){
            char c[100];
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            SelectareFisierTabla(c, text);
            if (c[0] == '\0'){
                ok = false;
            } else {
                startJoc(IncarcaTabla(c), nr_jucatori, text);
                ok = true;
            }
        }
    }
}