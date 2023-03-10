#include <graphics.h>
#include <iostream>
#include <math.h>

#define N 3
#define NMAX 3
#define PI 3.1415

using namespace std;

// desenarea (conversie real -> intreg)
void desen(int n,double P[]);
// inmultirea a doua matrici
void inmult(double A[3][3],double B[3][3]);
// inversarea unei matrici
void invers(int n, double a[NMAX][NMAX],double eps,
double b[NMAX][NMAX],double *det_a,
int *err);


int main()
{
    initwindow(800,700);

    int X=300;
    int Y=500;
    int rr=50;

    int i,x,y,e;
	double xc,yc,eps=exp(-9);
	double u, r, sinu, cosu, d ;
	double P[3][3]; // matricea varfurilor
	double O[3][3]; // matricea de Oglindire
	double R[3][3]; // matricea de Rotatie
	double Ri[3][3]; // matricea de Rotatie inversa
	double T[3][3]; // matricea de Translatie
	double Ti[3][3]; // matricea de Translatie inversa
	double M[3][3]; // matricea de transformare finala

	double P2[3][3]; // matricea varfurilor
	double O2[3][3]; // matricea de Oglindire
	double R2[3][3]; // matricea de Rotatie
	double Ri2[3][3]; // matricea de Rotatie inversa
	double T2[3][3]; // matricea de Translatie
	double Ti2[3][3]; // matricea de Translatie inversa
	double M2[3][3];

	double P3[3][3]; // matricea varfurilor
	double O3[3][3]; // matricea de Oglindire
	double R3[3][3]; // matricea de Rotatie
	double Ri3[3][3]; // matricea de Rotatie inversa
	double T3[3][3]; // matricea de Translatie
	double Ti3[3][3]; // matricea de Translatie inversa
	double M3[3][3];

    int x1,y1,x2,y2; // dreapta
	x1=300;y1=576;
	x2=300;y2=161;
    d=sqrt(x1*x1+y1*y1);
	sinu = (y2-y1)/d;
	cosu = (x2-x1)/d;
    int poligon[128];    // valori corespunzatoare dispozitivului de afisare
    double points[128];  // valori reale (utilizate in tansform geometrice)

    int RR = 95;
    double alfa = 2*PI/N;
    //constructie poligon
    for(int i=0;i<N+1;i++){
        points[2*i]   = RR*cos(i*alfa);
        points[2*i+1] = RR*sin(i*alfa);
    }
    // tre sa egalam elementele/coordonatele din cei 2 vectori (cred)
    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];
    //drawpoly(4,poligon);

    // TRANSLATATIA POLIGONULUI
    int tx = 185, ty = 275;
    for(int i=0;i<N+1;i++){
            points[2*i] = points[2*i] + tx;
            points[2*i+1]= points[2*i+1] + ty;
    }
    for(int i=0;i<2*N+2;i++) poligon[i]=(int)points[i];
    drawpoly(4,poligon);

    	// calculez coordonatele centrului
	for(xc=0,i=0;i<3;i++) xc+=poligon[2*i]; xc/=3;
	for(yc=0,i=0;i<3;i++) yc+=poligon[2*i+1]; yc/=3;

	// matricea P   coordonatele varfurilor
	for(int i=0;i<3;i++){
		P[i][0]=poligon[2*i];
		P[i][1]=poligon[2*i+1];
		P[i][2]=1;
	}

    // T - matricea de translatie
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) T[i][j]=1; else T[i][j]=0;
    T[2][0]=-x1;
    T[2][1]=-y1;

    // T - matricea de translatie inversa
    invers(3,T,eps,Ti,&d,&e);

    // R - matricea de rotatie
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    R[i][j]=0;
    R[0][0]=R[1][1]=cosu;
    R[0][1]=-sinu;
    R[1][0]=sinu;
    R[2][2]=1;

    // R - matricea de rotatie inversa
    invers(3,R,eps,Ri,&d,&e);

    // O - matricea de transformare de oglindire
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) O[i][j]=1; else O[i][j]=0;
    O[1][1]=-1; // oglindire fata de Ox

    // M - matricea de transformare compusa
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) M[i][j]=1; else M[i][j]=0;
    inmult(M,T);
    inmult(M,R);
    inmult(M,O);
    inmult(M,Ri);
    inmult(M,Ti);

    // se aplica matricea de transformare compusa
    inmult(P,M);

    // refac vectorul de noduri
    for(i=0;i<N;i++){
    poligon[2*i] = P[i][0];
    poligon[2*i+1] = P[i][1];
    }
    poligon[2*N]=poligon[0];poligon[2*N+1]=poligon[1];

    drawpoly(4,poligon); // desenez triunghiul in poz finala oglindita

    //Triunghiul de jos
    //coordonate obtinute cu ajutorul functiei getMouseCoordinates
    double poligon2[]={293,445,116,358,160,510,293,445};    // valori corespunzatoare dispozitivului de afisare
    //double points2[128];  // valori reale (utilizate in tansform geometrice)

   for(xc=0,i=0;i<3;i++) xc+=poligon2[2*i]; xc/=3;
	for(yc=0,i=0;i<3;i++) yc+=poligon2[2*i+1]; yc/=3;
	desen(N+1,poligon2);


	for(int i=0;i<3;i++){
		P2[i][0]=poligon2[2*i];
		P2[i][1]=poligon2[2*i+1];
		P2[i][2]=1;
	}

	// T - matricea de translatie
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) T2[i][j]=1; else T2[i][j]=0;
    T2[2][0]=-x1;
    T2[2][1]=-y1;

	invers(3,T2,eps,Ti2,&d,&e);

	//matricea de rotatie
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    R2[i][j]=0;
    R2[0][0]=R2[1][1]=cosu;
    R2[0][1]=-sinu;
    R2[1][0]=sinu;
    R2[2][2]=1;

    // R - matricea de rotatie inversa
    invers(3,R2,eps,Ri2,&d,&e);

    // O - matricea de transformare de oglindire
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) O2[i][j]=1; else O2[i][j]=0;
    O2[1][1]=-1; // oglindire fata de Ox

    // M - matricea de transformare compusa
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) M2[i][j]=1;
        else M2[i][j]=0;
    inmult(M2,T2);
    inmult(M2,R2);
    inmult(M2,O2);
    inmult(M2,Ri2);
    inmult(M2,Ti2);

    // se aplica matricea de transformare compusa
    inmult(P2,M2);

    // refac vectorul de noduri
    for(i=0;i<N;i++){
    poligon2[2*i] = P2[i][0];
    poligon2[2*i+1] = P2[i][1];
    }
    poligon2[2*N]=poligon2[0];poligon2[2*N+1]=poligon2[1];

    desen(N+1,poligon2); // desenez triunghiul in poz finala oglindita

    //coordonate obtinute cu functia getMouseCoordinates
    double poligon4[]={350,100,300,120,253,100,300,60,350,100};
    desen(5,poligon4);

    double poligon3[]={285,128,173,187,205,90,285,128}; // valori corespunzatoare dispozitivului de afisare

    for(xc=0,i=0;i<3;i++) xc+=poligon3[2*i]; xc/=3;
	for(yc=0,i=0;i<3;i++) yc+=poligon3[2*i+1]; yc/=3;
	desen(N+1,poligon3);

	for(int i=0;i<3;i++){
		P3[i][0]=poligon3[2*i];
		P3[i][1]=poligon3[2*i+1];
		P3[i][2]=1;
	}

	// T - matricea de translatie
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) T3[i][j]=1; else T3[i][j]=0;
    T3[2][0]=-x1;
    T3[2][1]=-y1;

	invers(3,T3,eps,Ti3,&d,&e);

	//matricea de rotatie
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    R3[i][j]=0;
    R3[0][0]=R3[1][1]=cosu;
    R3[0][1]=-sinu;
    R3[1][0]=sinu;
    R3[2][2]=1;

    // R - matricea de rotatie inversa
    invers(3,R3,eps,Ri3,&d,&e);

    // O - matricea de transformare de oglindire
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) O3[i][j]=1; else O3[i][j]=0;
    O3[1][1]=-1; // oglindire fata de Ox

    // M - matricea de transformare compusa
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    if(i==j) M3[i][j]=1;
        else M3[i][j]=0;
    inmult(M3,T3);
    inmult(M3,R3);
    inmult(M3,O3);
    inmult(M3,Ri3);
    inmult(M3,Ti3);

    // se aplica matricea de transformare compusa
    inmult(P3,M3);

    // refac vectorul de noduri
    for(i=0;i<N;i++){
    poligon3[2*i] = P3[i][0];
    poligon3[2*i+1] = P3[i][1];
    }
    poligon3[2*N]=poligon3[0];poligon3[2*N+1]=poligon3[1];

    desen(N+1,poligon3); // desenez triunghiul in poz finala oglindita


    double poligon5[]={285,575,285,630,315,630,315,575};
    desen(4,poligon5);

    setfillstyle(1,WHITE);
    floodfill(299,125,WHITE);

    //getMouseCoordinates();
    //cand functia e folosita ce e dedesubt nu se mai deseneaza
    //ar trebui folosita la final pentru a vedea tot

    getch();

    closegraph();
    return 0;
}

// reprezentare poligon
void desen(int n,double poly[]){
	int P[100];
	for(int i=0;i<2*n+2;i++){
		P[i]=(int)poly[i];
	}
	drawpoly(n,P);
}

// inmultirea a 2 matrici de 3 x 3 (coordonate omogene)
void inmult(double A[3][3], double B[3][3]){
	double X[3][3];
	int i,j,k;
	for(i=0;i<3;i++)
	for(j=0;j<3;j++)
	for(k=0,X[i][j]=0;k<3;k++)
		X[i][j]=X[i][j]+A[i][k]*B[k][j];
	for(i=0;i<3;i++)
	for(j=0;j<3;j++)A[i][j]=X[i][j];
}


// calculeaza inversa unei matrici
void invers(int n, double a[NMAX][NMAX],double eps,
double b[NMAX][NMAX],double *det_a,
int *err)
{
	int i,j,k,pozmax;
	double amax,aux;
	double X[NMAX][NMAX];
	// copiez prima matrice
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
		X[i][j]=a[i][j];
	/* Initializarea matricei b cu matricea unitate */
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
		if(i==j) b[i][j]=1.0;
	else b[i][j]=0.0;
	/* Initializarea determinantului */
	*det_a=1.0;
	/* Se face 0sub diagonala principala si 1 pe ea */
	k=0; /*k=nr.liniei */
	*err=0;
	while((k<n) && (*err==0))
	{
		/*Calcul element pivot*/
		amax=fabs(X[k][k]);pozmax=k;
		for(i=k+1;i<n;i++)
		if (fabs(X[i][k]) >amax) {
			amax=fabs(X[i][k]);
			pozmax=i;
		};
		/*Interschimbarea liniei k cu pozmax in matr. a si b */
		if( k!=pozmax) {
			for(j=0;j<n;j++){
				aux=X[k][j];
				X[k][j]=X[pozmax][j];
				X[pozmax][j]=aux;
				aux=b[k][j];
				b[k][j]=b[pozmax][j];
				b[pozmax][j]=aux;
			};
			*det_a=-*det_a;
		};
		if( fabs(X[k][k]) <eps) *err=1;
		else {
			*det_a =*det_a*X[k][k];
			aux=X[k][k];
			for(j=0;j<n;j++)
			{
				X[k][j]=X[k][j] / aux;
				b[k][j]=b[k][j] / aux;
			};
			for(i=0;i<n;i++)
				if(i!=k) {
					aux=X[i][k];
					for(j=0;j<n;j++)
					{
						X[i][j]=X[i][j]-X[k][j]*aux;
						b[i][j]=b[i][j]-b[k][j]*aux;
					}
				}
		}
		k++;
	}
}

