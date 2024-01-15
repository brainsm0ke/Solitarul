#pragma once
#include "limbi.h"

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

void startJoc(TablaDeJoc T, int nr_jucatori, text& text);

bool isInsideButton(int x, int y, int left, int top, int right, int bottom);