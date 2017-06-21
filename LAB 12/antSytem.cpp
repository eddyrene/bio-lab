#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;


typedef pair<int,int> tupla;
typedef vector<vector<double> > mat;

typedef struct {
	vector<char> visited;
	vector<char> enables;
}hormiga;

mat MT; //matriz de transcion , distancia
mat MF; //matriz de Feromonas
mat MV; //matriz de Visibilidad


void printHormiga(hormiga &a)
{
	cout<<"visitados"<<" - ";
	for(auto w :a.visited)
		cout<<w<<" ";	
	cout<<"disponibles"<<" - ";
	for(auto w: a.enables)
		cout<<w<<" ";
}
void printHormiguero(string a, vector<hormiga> &h)
{
	cout<<a;
	for(int i=0;i<h.size();i++)
	{
		printHormiga(h[i]);
		cout<<endl;
	}
}
void startHormiguero(vector<hormiga> &a, int cant, int f)
{
	a.resize(cant);
	for(int i=0;i<a.size();i++)
	{
		a[i].visited.resize(f);
		a[i].enables.resize(f);
	}

	for(int i=0;i<a.size();i++)
	{
		a[i].visited[0]='0';
		a[i].visited[1]='0';
		a[i].visited[2]='0';
		a[i].visited[3]='0';
		a[i].visited[4]='0';
		a[i].enables[0]='A';
		a[i].enables[1]='B';
		a[i].enables[2]='C';
		a[i].enables[3]='D';
		a[i].enables[4]='E';
	}
}
int start(int f , int c, double fi)
{
	MT.resize(f);
	for(int i=0;i<f;i++)
		MT[i].resize(c);

	MT[0][0]=0; 	MT[0][1]=12;	MT[0][2]=3;		MT[0][3]=23;	MT[0][4]=1;
	MT[1][0]=12; 	MT[1][1]=0;		MT[1][2]=9;		MT[1][3]=18;	MT[1][4]=3;
	MT[2][0]=3;		MT[2][1]=9;		MT[2][2]=0;		MT[2][3]=89;	MT[2][4]=56;
	MT[3][0]=23; 	MT[3][1]=18;	MT[3][2]=89;	MT[3][3]=0;		MT[3][4]=87;
	MT[4][0]=1; 	MT[4][1]=3;		MT[4][2]=56;	MT[4][3]=87;	MT[4][4]=0;

	MF.resize(f);
	for(int i=0;i<f;i++)
		MF[i].resize(c);
	
	for(int i=0;i<f;i++)
		for(int j=0;j<c;j++) 
			MF[i][j]=fi;

	MV.resize(f);
	for(int i=0;i<f;i++)
		MV[i].resize(c);	

}

void printMat(string text, mat a, int f, int c)
{
	cout<<text;
	for(int i=0;i<f;i++)
	{
		for(int j=0;j<c;j++)
			cout<<a[i][j]<<" ";
		cout<<endl;		
	}	
}
void matrixVisilibidad(int f, int c)
{	
	for(int i=0;i<f;i++)
		for(int j=0;j<c;j++)
			MV[i][j]=1/MT[i][j];

}

double genRandom(double li, double ls)
{
	//srand (time(NULL));
	return li + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(ls-li)));
}
int  ruleta(int ciuIni, int columnas)
{
	double ruleta=0;
	vector<double> vProb; vProb.resize(columnas,0);
	vector<double> vCoste; vCoste.resize(columnas,0);
	cout<<"Activaciones"<<endl;
	for(int i=0;i<columnas;i++)
	{
		if(i!=ciuIni)
		{	
			vCoste[i]=MF[ciuIni][i]* MV[ciuIni][i]; 
			ruleta += vCoste[i];
			//cout<<MF[ciuIni][i]* MV[ciuIni][i]<<endl;
			cout<<vCoste[i]<<endl;
		}
	}
	cout<<"suma: "<<ruleta<<endl<<"probabilidades: "<<endl;
	for(int i=0;i<columnas;i++)
	{
		if(i!=ciuIni)
		{
			vProb[i]=ruleta/vCoste[i];
			cout<<vProb[i]<<endl;
		}
	}
	double r= genRandom(0,1);
	cout<<"Numero aleatorio :"<<r<<endl;
	double acu=0;
	for(int i=0;i<vProb.size();i++)
	{
		acu+=vProb[i];
		cout<<"acumnulado: "<<acu<<endl;
		if(r<=acu)	
			return i;
	}
	return columnas-1;
}

int main()
{
	int cantHormigas=4;
	vector<hormiga> hormiguero;
	int alfa=1; int beta=1; int Q=1; int p= 0.99; int maxitera=100;
	int filas = 5; int columnas = 5; double feromona=0.1;
	start(filas,columnas,feromona);
	printMat("\n Matriz de distancia \n \n", MT, filas, columnas);
	printMat("\n Matriz de feromonas \n \n", MF, filas, columnas);
	matrixVisilibidad(filas, columnas);
	printMat("\n Matriz de visibilidad \n \n", MV, filas, columnas);
	startHormiguero(hormiguero,cantHormigas, filas);
	printHormiguero("\n Imprimiendo Hormiguero \n",hormiguero);
	int ciuIni=3;//D
	//Matriz de feromonas por visibilidad
	int next=ruleta(ciuIni,columnas);
	cout<<"siguiente estado: "<< next <<endl;


	return 0;
}