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
    "TODO",
    "Alege un alt tabel",
    "Jucator 1",
    "Jucator 2",
    "Ai castigat!",
    "Ai pierdut!",
    "Jucatorul 1 castiga!",
    "Jucatorul 2 castiga!",
    "Egalitate!"
};

text Engleza = {
    "One player",
    "Two players",
    "TODO",
    "Choose another table",
    "Player 1",
    "Player 2",
    "You win!",
    "You lose!",
    "Player 1 wins!",
    "Player 2 wins!",
    "It's a tie!"
};


int main() {
    initwindow(800,600,"Solitar");
    setbkcolor(LIGHTGRAY);
    clearviewport();
//    startJoc(IncarcaTabla("Tabla2.txt"),1, Romana);
}