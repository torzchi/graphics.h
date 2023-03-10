
#include <graphics.h>
#include <cmath>

#define N 5
#define PI 3.1415

void waitForLeftMouseClick();

int main()
{
    initwindow(800,600); //open a 800 x 600 graphics window

    int poligon[128];    // valori corespunzatoare dispozitivului de afisare
    double points[128];  // valori reale (utilizate in tansform geometrice)

    int R = 50;
    double alfa = 2*PI/N;
    for(int i=0;i<N+1;i++){
        points[2*i]   = R*cos(i*alfa);
        points[2*i+1] = R*sin(i*alfa);
    }

    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];

    //setcolor(YELLOW);
    //drawpoly(N+1,poligon);

    // translatia poligonului
    int tx = 230, ty = 170;
    for(int i=0;i<N+1;i++){
            points[2*i] = points[2*i] + tx;
            points[2*i+1]= points[2*i+1] + ty;
    }

    // calculez coordonatele centrului de greutate
    double xc=0, yc=0;
    for(int i=0;i<N;i++){
            xc += points[2*i];
            yc += points[2*i+1];
    }
    xc/=N;yc/=N;
    //circle((int)xc, (int)yc, 4);

    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];
    //setcolor(WHITE);
    //drawpoly(N+1,poligon);


    tx = 150;
    ty = 150;

    double Xc = xc+tx, Yc=yc+ty;
    //line(xc,yc, Xc, Yc);
    circle((int)Xc, (int)Yc, 4);
    // translatie
    for(int i=0;i<N+1;i++){
            points[2*i] = points[2*i] + tx;
            points[2*i+1]= points[2*i+1] + ty;
    }


    // scalare
    double Sx=2.5, Sy=2.5;
    for(int i=0;i<N+1;i++){
            points[2*i]   = Xc + (-Xc+points[2*i])   * Sx;
            points[2*i+1] = Yc + (-Yc+points[2*i+1]) * Sy;
    }
    //points[2*N] = points[0];
    //points[2*N+1] = points[1];

    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];
    setcolor(WHITE);
    drawpoly(N+1,poligon);

 waitForLeftMouseClick();

    // rotatia fata de centrul (Xc,Yc)
    double cosa = cos(PI/4), sina = sin(PI/4);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = points[2*i];
            yi = points[2*i+1];
            points[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            points[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];
    setcolor(YELLOW);
    drawpoly(N+1,poligon);

    // trasarea cercului
    double a;
    setcolor(WHITE);
    for(a=0;a<2*PI;a+=0.1)
        //putpixel(Xc+R*cos(a)*Sx, Yc+R*Sy*sin(a), RED);
        circle(Xc+R*cos(a)*Sx, Yc+R*Sy*sin(a), 4);


    // while(!kbhit());     // wait for user to press a key
    waitForLeftMouseClick(); // use one or the other of these--not both


    closegraph();        //close graphics window
	return 0;
}





void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}


