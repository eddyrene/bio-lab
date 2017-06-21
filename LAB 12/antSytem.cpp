#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;


typedef pair<int,int> tupla;
typedef vector<vector<double> > mat;

typedef struct {
	vector<tupla> visited;
	vector<char> enables;
	string outString;
}hormiga;


mat MT;
mat MF;
mat MV;

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
int main()
{
	int filas = 5; int columnas = 5; double feromona=0.1;
	start(filas,columnas,feromona);
	printMat("Matriz de distancia \n", MT, filas, columnas);
	printMat("Matriz de feromonas \n", MF, filas, columnas);
	matrixVisilibidad(filas, columnas);
	printMat("Matriz de visibilidad \n", MV, filas, columnas);
	return 0;
}