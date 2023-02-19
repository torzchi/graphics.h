#include <iostream>
#include <math.h>
#include <graphics.h>

#define N 8
#define PI 3.1415

using namespace std;

void bezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    double t;
    int x, y;

    for (t = 0.0; t <= 1.0; t += 0.0005) {
        x = pow(1-t,3)*x0 + 3*t*pow(1-t,2)*x1 + 3*pow(t,2)*(1-t)*x2 + pow(t,3)*x3;
        y = pow(1-t,3)*y0 + 3*t*pow(1-t,2)*y1 + 3*pow(t,2)*(1-t)*y2 + pow(t,3)*y3;
        putpixel(x, y, GREEN);
    }
}

int main()
{
    initwindow(900, 700);

    int poli[]={320,50,320,320,100,320,320,800,320,50,320,320,540,320,320,800};

    // Define points of the Bezier curve
    int x0 = poli[0], y0 = poli[1];           // Start point
    int x1 = poli[2], y1 = poli[3];           // Control point 1
    int x2 = poli[4], y2 = poli[5];           // Control point 2
    int x3 = poli[6], y3 = poli[7];           // Final point

    int X0 = poli[8], Y0 = poli[9];           // Start point
    int X1 = poli[10], Y1 = poli[11];           // Control point 1
    int X2 = poli[12], Y2 = poli[13];           // Control point 2
    int X3 = poli[14], Y3 = poli[15];           //Final point

    // Draw the Bezier curve
    setcolor(WHITE);
    //bezier(x0, y0, x1, y1, x2, y2, x3, y3);//prima curba
    //bezier(X0,Y0,X1,Y1,X2,Y2,X3,Y3);  //curba oglindita


    // TRANSLATATIA POLIGONULUI
    int tx = 0, ty = 0;
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + tx;
            poli[2*i+1]= poli[2*i+1] + ty;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    //bezier(x0, y0, x1, y1, x2, y2, x3, y3); //prima curba
    //bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita


    double xc=0, yc=0;
    for(int i=0;i<N;i++){
            xc += poli[2*i];
            yc += poli[2*i+1];
    }
    xc/=N;yc/=N;
    //circle(xc,yc,5);

    //TRANSLATARILE(coordonatele) se aduna intre ele deoarece poligonul e construit doar dupa SCALARE
    //insa daca a doua ar fi (0,0) prima n ar avea sens ca nu are ce translata inca (Oarecum)
    //pratic a doua TRANSLATARE porneste in continuarea primei

    tx =-100;
    ty = 0;

    //Avem doua TRANSLATARI, prima are loc inainte de ROTATIE si SCALARE, iar a doua TRANSLATATIE are rol dupa
    // indiferent ca sunt scrise una dupa alta

    double Xc = xc+tx, Yc=yc+ty;
    //circle((int)Xc, (int)Yc, 4);//face un cerc in centrul de greutate
    //TRANSLATATIE 2
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + tx;
            poli[2*i+1]= poli[2*i+1] + ty;
    }

    // scalare
    double Sx=.5, Sy=.5;
    for(int i=0;i<N+1;i++){
            poli[2*i]   = Xc + (-Xc+poli[2*i])   * Sx;
            poli[2*i+1] = Yc + (-Yc+poli[2*i+1]) * Sy;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    //bezier(x0, y0, x1, y1, x2, y2, x3, y3);
    //bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

     //ROTATIA FATA DE CENTRUL (Xc,Yc)
    double cosa = cos(2*PI/5), sina = sin(2*PI/5);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = poli[2*i];
            yi = poli[2*i+1];
            poli[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            poli[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    bezier(x0, y0, x1, y1, x2, y2, x3, y3);
    bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    //ROTATIA FATA DE CENTRUL (Xc,Yc)
    //double cosa = cos(2*PI/5), sina = sin(2*PI/5);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = poli[2*i];
            yi = poli[2*i+1];
            poli[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            poli[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    //bezier(x0, y0, x1, y1, x2, y2, x3, y3);
    //bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    // TRANSLATATIA POLIGONULUI
    int Tx = 60, Ty = -180;
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + Tx;
            poli[2*i+1]= poli[2*i+1] + Ty;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    bezier(x0, y0, x1, y1, x2, y2, x3, y3); //prima curba
    bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    //ROTATIA FATA DE CENTRUL (Xc,Yc)
    //double cosa = cos(2*PI/5), sina = sin(2*PI/5);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = poli[2*i];
            yi = poli[2*i+1];
            poli[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            poli[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    //bezier(x0, y0, x1, y1, x2, y2, x3, y3);
    //bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    // TRANSLATATIA POLIGONULUI
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + Tx;
            poli[2*i+1]= poli[2*i+1] + Ty;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    bezier(x0, y0, x1, y1, x2, y2, x3, y3); //prima curba
    bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    //ROTATIA FATA DE CENTRUL (Xc,Yc)
    //double cosa = cos(2*PI/5), sina = sin(2*PI/5);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = poli[2*i];
            yi = poli[2*i+1];
            poli[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            poli[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    //bezier(x0, y0, x1, y1, x2, y2, x3, y3);
    //bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    // TRANSLATATIA POLIGONULUI
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + Tx;
            poli[2*i+1]= poli[2*i+1] + Ty;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    bezier(x0, y0, x1, y1, x2, y2, x3, y3); //prima curba
    bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    //ROTATIA FATA DE CENTRUL (Xc,Yc)
    //double cosa = cos(2*PI/5), sina = sin(2*PI/5);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = poli[2*i];
            yi = poli[2*i+1];
            poli[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            poli[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    //bezier(x0, y0, x1, y1, x2, y2, x3, y3);
    //bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita

    // TRANSLATATIA POLIGONULUI
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + Tx;
            poli[2*i+1]= poli[2*i+1] + Ty;
    }

    x0 = poli[0], y0 = poli[1];           // Start point
    x1 = poli[2], y1 = poli[3];           // Control point 1
    x2 = poli[4], y2 = poli[5];           // Control point 2
    x3 = poli[6], y3 = poli[7];           // Final point

    X0 = poli[8], Y0 = poli[9];           // Start point
    X1 = poli[10], Y1 = poli[11];           // Control point 1
    X2 = poli[12], Y2 = poli[13];           // Control point 2
    X3 = poli[14], Y3 = poli[15];           //Final point

    bezier(x0, y0, x1, y1, x2, y2, x3, y3); //prima curba
    bezier(X0, Y0, X1, Y1, X2, Y2, X3, Y3);  //curba oglindita


    getch();
    closegraph();
    return 0;
}
