#include <iostream>
#include <graphics.h>
#include <winbgim.h>


using namespace std;

int main()
{
    int w = 800, h = 600;
    initwindow(w,h);
    rectangle();
    getch();
    closegraph();
    return 0;
}
