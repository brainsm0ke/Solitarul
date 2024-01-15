#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <sstream>
#include <string.h>

#include "joc.h"
#include "tabla.h"
#include "limbi.h"

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



int main() {
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