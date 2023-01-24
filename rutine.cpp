#include <stdio.h>
#include <math.h>
#include <winbgim.h>

//PT OGLINDIT (u = PI - atan(m), m = panta dreptei)
double OGX (int X, int Y, int a, int b, int c, double u){

    return 2*fabs(a*X+b*Y+c)/sqrt(a*a+b*b)*sin(u);

}

double OGY (int X, int Y, int a, int b, int c, double u){

    return 2*fabs(a*X+b*Y+c)/sqrt(a*a+b*b)*cos(u);

}

//PT rotatie
double rotatieX(double x, double y, int xo, int yo, double U){

double dx = (x-xo)*cos(U) - (y-yo)*sin(U);
return xo + dx;

}

double rotatieY(double x, double y, int xo, int yo, double U){

double dy = (x-xo)*sin(U) + (y-yo)*cos(U);
return yo + dy;

}

//DDA

void DDAline(int x1, int y1, int x2, int y2, int ColorD){

    float dx, dy, step;
    float xinc, yinc, ct, x, y;
    dx = x1-x2;
    dy = y1-y2;
    if(fabs(dx)>fabs(dy))
        step = fabs(dx);
    else step = fabs(dy);

    xinc = dx/step;
    yinc = dy/step;

    x=x1;
    y=y1;

    for(ct=1;ct<=step;ct++){
        putpixel((int)x, (int)y, ColorD);
        x-=xinc;
        y-=yinc;
    }
return;
}

//Mouse input

void waitForLeftMouseClick(int &x, int &y){
    clearmouseclick(WM_LBUTTONDOWN);
 const int DELAY = 50;
 while (!ismouseclick(WM_LBUTTONDOWN))
 delay(DELAY);
 getmouseclick(WM_LBUTTONDOWN, x, y);

}
