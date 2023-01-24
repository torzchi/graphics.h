/*
  Un obiect se deplaseaza pe o traiectorie rectilinie,
  iar la trecerea printr-o zona predefinita
  isi modifica culoarea conturului

  (este exemplificata decuparea)
*/

#include <winbgim.h>
#include <math.h>
#define Nvf 4
#define N 6



// obiectul initial
 int obj[2*Nvf+2] = {0,70,  -25,0,   0,20,  25,0,   0,70};

// buffer (obiectul transformat)
int obt[2*Nvf+2] = {0};

// coordonate careu
int xmin=120, ymin=110, xmax=360, ymax=280;
int xi1,yi1,xi2,yi2;

void waitForLeftMouseClick(int& x, int& y);
int codif(int x, int y);
int CohenSutherland(int x1i,int y1i,int x2i,int y2i,
int* x1d,int* y1d, int* x2d,int* y2d);

// traseaza o linie in careu (cu decupare)
void Line(int xi1,int yi1,int xi2,int yi2){
     int x1,y1,x2,y2;
     setcolor(2);
     line(xi1,yi1,xi2,yi2);
     CohenSutherland(xi1,yi1,xi2,yi2,&x1,&y1,&x2,&y2);
     //if((x1!=xi1)||(x2!=xi2)||(y1!=yi1)||(y2!=yi2))
     setcolor(3);
     line(x1,y1,x2,y2);
};

// translatie + rotatie
void Ro(double alfa){
int xR, yR;
double sina=sin(alfa),
       cosa=cos(alfa);
double x,y;

for(int i=0;i<2*Nvf+2;i+=2)xR+=obt[i];
for(int i=1;i<2*Nvf+2;i+=2)yR+=obt[i];
xR/=Nvf;
yR/=Nvf;

for(int i=0;i<2*Nvf+2;i+=2){
	x = obt[ i ];
	y = obt[i+1];
	obt[ i ] = xR + (int)((x-xR) * cosa - (y-yR) * sina);
	obt[i+1] = yR + (int)((x-xR) * sina + (y-yR) * cosa);
    }
}

// translatie
void Tr(int Dx, int Dy){
for(int i=0;i<2*Nvf+2;i+=2){
	obt[ i ] = Dx + obj[ i ];
	obt[i+1] = Dy + obj[i+1];
}

}

void dsn(){
for(int i=0;i<2*Nvf;i+=2)
Line(obt[i],obt[i+1],obt[i+2],obt[i+3]);
}


void hex()
{
     double points[128];
       int poligon[128];
     int R = 50;
    double alfa = 2*M_PI/N;
    for(int i=0;i<N+1;i++){
        points[2*i]   = R*cos(i*alfa);
        points[2*i+1] = R*sin(i*alfa);
    }
    points[12]=points[0];
    points[13]=points[1];
    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];

     int tx = 350, ty = 170;
    for(int i=0;i<N+1;i++){
            points[2*i] = points[2*i] + tx;
            points[2*i+1]= points[2*i+1] + ty;
    }
    points[12]=points[0];
    points[13]=points[1];
    for(int i=0;i<N;i++){
            {
                Line( points[2*i], points[2*i+1], points[2*i+2], points[2*i+3]);
            }

}

}
int main(){
 int x1,y1,x2,y2;
 initwindow(540,480);
 setcolor(2);
 rectangle(xmin,ymin,xmax,ymax);
 //setwritemode(XOR_PUT);
 //Tr(10,10);Ro(-3.1415/5);


  hex();
 /*
 dsn();
 for(int k=10;k<400;k+=15){
     dsn();   // sterge
     Tr(k,0.6*k);Ro(-3.1415/5);
     dsn();   // deseneaza
     delay(100);
     if(ismouseclick(WM_LBUTTONDOWN)) break;

 }
 */


 /*
 while(1){
   waitForLeftMouseClick(xi1,yi1);
   waitForLeftMouseClick(xi2,yi2);
   Line(x1,y1,x2,y2);
 }
 */

 waitForLeftMouseClick(x1,y1);
 closegraph(); //close graphics window
 return 0;
}



void waitForLeftMouseClick(int& x, int& y){
clearmouseclick(WM_LBUTTONDOWN);
const int DELAY = 50; // Milliseconds of delay between checks
//int x, y;
while (!ismouseclick(WM_LBUTTONDOWN))
delay(DELAY);
getmouseclick(WM_LBUTTONDOWN, x, y);
}


int codif(int x, int y){
int cod;
cod=(x < xmin) ? 1:0;
if(x > xmax) cod=2;
if(y < ymin) cod |=4;
if(y > ymax) cod |=8;
return cod;
}

int CohenSutherland(int x1i,int y1i,int x2i,int y2i,
int* x1d,int* y1d, int* x2d,int* y2d){
int acceptat,rejectat,vertical;
float m, x1=x1i, y1=y1i, x2=x2i, y2=y2i;
int cod1,cod2;
float t;
acceptat=rejectat=vertical=0;
if (x1i != x2i)
m=(y2-y1)/(x2-x1);
else
vertical=1;
do{
cod1=codif((int)x1,(int)y1);
cod2=codif((int)x2,(int)y2);
if(cod1==0 && cod2==0) { acceptat=1; break;}
if((cod1 & cod2) !=0 ) { rejectat=1; break;}
if(cod1==0)
{t=x1;x1=x2;x2=t; t=y1;y1=y2;y2=t; //inversare capete
cod1=cod2;
}
if(cod1 & 1)
{ y1+=(xmin-x1)*m;
x1=xmin;
}
else
if(cod1 & 2){
y1+=(xmax-x1)*m;
x1=xmax;}
else if(cod1 & 4)
{ if (!vertical)
x1+=(ymin-y1)/m;
y1=ymin;}
else
{if (!vertical)
x1+=(ymax-y1)/m;
y1=ymax;
}
} while ( acceptat==rejectat);
if(acceptat){*x1d=(int)x1; *y1d=(int)y1;
*x2d=(int)x2; *y2d=(int)y2;
return 1;
}
return 0;
}





