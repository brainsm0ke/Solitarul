#include <iostream>
#include <graphics.h>
#include <winbgim.h>


using namespace std;

int main()
{
    int w = 800, h = 600;
    initwindow(w,h);
    rectangle(100,100,200,200);
    getch();
    closegraph();
    return 0;
}
