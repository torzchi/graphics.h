#include <graphics.h>
#include <iostream>
#include <math.h>
#define N 6
#define PI 3.14159265
using namespace std;

void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

int main()
{

    initwindow(800,600); //open a 800x600 graphics window

      int points[14]={0};
      int i,n = 6, R = 120, Xc=400, Yc=300;
      // completez coordonatele poligonului regulat cu n=6 varfuri (hexagon)
      for(int i=0;i<n;i++){
          double alfa = i * 2*PI/n;
          points[2*i]   = Xc + R * cos(alfa);
          points[2*i+1] = Yc + R * sin(alfa);
      }
      points[12]=points[0];
      points[13]=points[1];

      setcolor(YELLOW);
      drawpoly(n+1,points);

      //Scalare
///////////////////////////////////////////////////////////////////////////
    double scalingFactor=0.2;
    double S[3][3] = {{scalingFactor, 0, 0}, {0, scalingFactor, 0}, {0, 0, 1}};

    // Multiply each vertex of the hexagon with the scaling matrix
    for (int i = 0; i < n; i++) {
        double a = points[i*2], b = points[i*2+1], c = 1;
        points[2*i] = S[0][0]*a + S[0][1]*b + S[0][2]*c;
        points[2*i+1] = S[1][0]*a + S[1][1]*b + S[1][2]*c;
    }
    points[12]=points[0];
    points[13]=points[1];

   // waitForLeftMouseClick();
    //cleardevice();
    //drawpoly(N+1,points);
////////////////////////////////////////////////////////////////////////
 // Rotation

double unghi=-25;

double angle = unghi * M_PI / 180;


    double Ro[3][3] = {{cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};

    // Multiply each vertex of the hexagon with the rotation matrix
    for (int i = 0; i < 6; i++) {
        double a = points[i*2], b = points[i*2+1], c = 1;
        points[2*i] = Ro[0][0]*a + Ro[0][1]*b + Ro[0][2]*c;
        points[2*i+1] = Ro[1][0]*a + Ro[1][1]*b + Ro[1][2]*c;
    }
     points[12]=points[0];
      points[13]=points[1];

  //waitForLeftMouseClick();
    //cleardevice();
   // drawpoly(n+1,points);

////////////////////////////////////////////////////////////////////////
//MIRROR
 // Mirroring matrix
    double M[3][3] =  {{1,0,0},{0,-1,0},{0,0,1}};;
    for(int i=0;i<3;i++)
for(int j=0;j<3;j++)
if(i==j) M[i][j]=1; else M[i][j]=0;
M[1][1]=-1; // oglindire fata de Ox

    // Multiply each vertex of the hexagon with the mirroring matrix
    for (int i = 0; i < 6; i++) {
            double a = points[i*2], b = points[i*2+1], c = 1;
         points[2*i] = M[0][0]*a + M[0][1]*b + M[0][2]*c;
        points[2*i+1] = M[1][0]*a + M[1][1]*b + M[1][2]*c;
    }
     points[12]=points[0];
      points[13]=points[1];

  waitForLeftMouseClick();
    cleardevice();
    drawpoly(n+1,points);
////////////////////////////////////////////////////////////////////////////


    getch();
    closegraph();
    return 0;
}
