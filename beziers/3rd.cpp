#include <graphics.h>
#include <iostream>
#include <cmath>
#define n 4
#define PI 3.14

using namespace std;

void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50;
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

#include <cstdio>

struct point
{
    float x;
    float y;
};

// simple linear interpolation between two points
void lerp(point& dest, const point& a, const point& b, const float t)
{
    dest.x = a.x + (b.x-a.x)*t;
    dest.y = a.y + (b.y-a.y)*t;
}

// evaluate a point on a bezier-curve. t goes from 0 to 1.0
void bezier(point &dest, const point& a, const point& b, const point& c, const point& d, const float t)
{
    point ab,bc,cd,abbc,bccd;
    lerp(ab, a,b,t);           // point between a and b (green)
    lerp(bc, b,c,t);           // point between b and c (green)
    lerp(cd, c,d,t);           // point between c and d (green)
    lerp(abbc, ab,bc,t);       // point between ab and bc (blue)
    lerp(bccd, bc,cd,t);       // point between bc and cd (blue)
    lerp(dest, abbc,bccd,t);   // point on the bezier-curve (black)
}


int main()
{
    initwindow(900,900);
    setcolor(GREEN);
    point a = { 320, 50 };
    point b = { 320, 320  };	//line(a.x,a.y,b.x,b.y);
    point c = { 100, 320 };
    point d = { 320, 800 };	//line(c.x,c.y,d.x,d.y);

    point p,q;
    double xc=0, yc=0;
    for (int i=0; i<1000; ++i)
    {

		float t = static_cast<float>(i)/999.0;
		bezier(p,a,b,c,d,t);

		putpixel(p.x,p.y,RED);
		putpixel(320*2-p.x,p.y,RED); //oglindeirea primei curbe


        xc=xc+p.x+(320*2-p.x);
        yc=yc+p.y;



    }
    xc=xc/1000/2;yc=yc/1000;// coordonate centru de greutate
    circle(int(xc),int(yc),7);
    cout<<xc<<" "<<yc;



    waitForLeftMouseClick();
    return 0;
}

