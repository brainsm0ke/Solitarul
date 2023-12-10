#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include<graphics.h>
#include<winbgim.h>
#define MAX 25
using namespace std;
int stanga,sus,width,height,latura,numar = 7;
bool gata;
void desen()
{
   int i,j;
   width = 400;
   height = 400;
   latura = width/numar;
   sus = (getmaxy() - width)/2;
   stanga=(getmaxx() - height)/2;
   setbkcolor(11); clearviewport(); setcolor(1);
   for (i = 1; i <= numar; i++)
       for (j = 1; j <= numar; j++)
           rectangle(stanga + latura * (i - 1),sus + latura * (j - 1),stanga + latura * i,sus + latura * j);
}
void deseneazaPiesa(int linia, int coloana)
{
    int x1,y1,x2,y2,xmijloc,ymijloc;
    setcolor(11); setfillstyle(SOLID_FILL,11);
    x1=stanga+latura*(coloana-1); y1=sus+latura*(linia-1);
    x2=x1+latura; y2=y1+latura;
    xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(1); setfillstyle(SOLID_FILL,1);
    fillellipse(xmijloc,ymijloc,18,18);
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
   deseneazaPiesa(i,j);
    }
   getch();
   closegraph();
   return 0;
}


