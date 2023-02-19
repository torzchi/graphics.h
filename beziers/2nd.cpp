#include <winbgim.h>
void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

struct point
{
    float x;
    float y;
};
void lerp(point& dest, const point& a, const point& b, const float t)
{
    dest.x = a.x + (b.x-a.x)*t;
    dest.y = a.y + (b.y-a.y)*t;
}

void bezier(point &dest, const point& a, const point& b, const point& c, const point& d, const float t)
{
    point ab,bc,cd,abbc,bccd;
    lerp(ab, a,b,t);
    lerp(bc, b,c,t);
    lerp(cd, c,d,t);
    lerp(abbc, ab,bc,t);
    lerp(bccd, bc,cd,t);
    lerp(dest, abbc,bccd,t);
}

int main()
{
    initwindow(1000,1000);
    int points[16]= {320,50,320,320,100,320,320,800,320,50,320,320,540,320,320,800};
    setcolor(YELLOW);
    point a = { 320, 50 };
    circle(a.x,a.y,4);
    point b = { 320, 320  };
    circle(b.x,b.y,4);
    line(a.x,a.y,b.x,b.y);
    point c = { 100, 320 };
    circle(c.x,c.y,4);
    point d = { 320, 800 };
    circle(d.x,d.y,4);
    line(c.x,c.y,d.x,d.y);

    for (int i=0; i<1000; ++i)
    {
        point p;
        float t = static_cast<float>(i)/999.0;
        bezier(p,a,b,c,d,t);

        putpixel(p.x,p.y,GREEN);
    }
    //line(320,50,320,800);
    setcolor(YELLOW);
    point a1 = { 320, 50 };
    circle(a1.x,a1.y,4);
    point b1 = { 320, 320  };
    circle(b1.x,b1.y,4);
    line(a1.x,a1.y,b1.x,b1.y);
    point c1 = { 540, 320 };
    circle(c1.x,c1.y,4);
    point d1 = { 320, 800 };
    circle(d1.x,d1.y,4);
    line(c1.x,c1.y,d1.x,d1.y);

    for (int i=0; i<1000; ++i)
    {
        point p;
        float t = static_cast<float>(i)/999.0;
        bezier(p,a1,b1,c1,d1,t);

        putpixel(p.x,p.y,GREEN);
    }
    setcolor(YELLOW);
    line(540,320,320,800);
    // calculez coordonatlele centrului de greutate
    double xc=0,yc=0;
    for(int i=0; i<=16; i++)
    {

        xc+=points[2*i];
        yc+=points[2*i+1];
    }
    xc=xc/8;
    yc=yc/8;
    circle(xc,yc,40);
    //scalare
    int tx=100,ty=100;
    double Xc = xc+tx, Yc=yc+ty;
    double sx=0.5,sy=0.5;

    for(int i=0; i<=16; i++)
    {

        points[2*i]=Xc+(-Xc+points[2*i])*sx;
        points[2*i+1]=Yc+(-Yc+points[2*i+1])*sy;
    }
// rotatie



    waitForLeftMouseClick();
    return 0;
}
