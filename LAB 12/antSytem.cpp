#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <iterator>
#include <fstream>
#include <cstdio>
#include <sstream>


using namespace std;

typedef pair<int,int> tupla;
typedef vector<vector<double> > mat;

typedef struct {
	vector<int> camino;
	list<char> enables;
	double fitness;
}hormiga;

mat MT; //matriz de transcion , distancia
mat MF; //matriz de Feromonas
mat MV; //matriz de Visibilidad

bool compare(hormiga a, hormiga b)
{
	if(a.fitness<b.fitness) return true; return false;
}

void printHormiga(hormiga &a)
{
	cout<<"visitados"<<" - ";
	for(auto w :a.camino)
		cout<<w<<" ";	
	cout<<"disponibles"<<" - ";
	for(auto w: a.enables)
		cout<<w<<" ";
	cout<<"fitness  "<< a.fitness;
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
	/*for(int i=0;i<a.size();i++)
	{
		a[i].visited.resize(f);
		a[i].enables.resize(f);
	}*/
	//a.camino.clear();
	for(int i=0;i<a.size();i++)
	{
		a[i].camino.clear();
		a[i].enables.push_back('A');
		a[i].enables.push_back('B');
		a[i].enables.push_back('C');
		a[i].enables.push_back('D');
		a[i].enables.push_back('E');
		a[i].enables.push_back('F');
		a[i].enables.push_back('G');
		a[i].enables.push_back('H');
		a[i].enables.push_back('I');
		a[i].enables.push_back('J');
	}
}

void readMat(string name)
{
    ifstream file(name);
    int m=0;
    string line;
    while(getline(file,line) )
    {
        int n=0;
        bool flag= false;
        std::stringstream   linestream(line);
        std::string         value;
        //cout<<"entro"<<endl;
        while(getline(linestream,value,' '))
        {
            int v = atoi(value.c_str());
            MT[m][n]=v;
            n++;
        }
     	m++;
    }
        
}


int start(int f , int c, double fi)
{
	MT.resize(f);
	for(int i=0;i<f;i++)
		MT[i].resize(c);
/*
	MT[0][0]=0; 	MT[0][1]=12;	MT[0][2]=3;		MT[0][3]=23;	MT[0][4]=1;
	MT[1][0]=12; 	MT[1][1]=0;		MT[1][2]=9;		MT[1][3]=18;	MT[1][4]=3;
	MT[2][0]=3;		MT[2][1]=9;		MT[2][2]=0;		MT[2][3]=89;	MT[2][4]=56;
	MT[3][0]=23; 	MT[3][1]=18;	MT[3][2]=89;	MT[3][3]=0;		MT[3][4]=87;
	MT[4][0]=1; 	MT[4][1]=3;		MT[4][2]=56;	MT[4][3]=87;	MT[4][4]=0;*/
	readMat("mat.txt");
	MF.resize(f);
	for(int i=0;i<f;i++)
		MF[i].resize(c);
	
	for(int i=0;i<f;i++)
		for(int j=0;j<c;j++) 
			if(i!=j)
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

void ruleta(int alfa, int beta, int ciuIni, int columnas, vector<hormiga> &hor)
{
	cout<<"Activaciones"<<endl;
	for(int h=0; h<hor.size(); h++)
	{
		cout<<"*******HORMIGA: "<<h<<endl;
		double ruleta=0;
		vector<double> vProb;
		vProb.resize(columnas,0);
		vector<double> vCoste; vCoste.resize(columnas,0);
		//for(int i=0;i<hor;[h].enables.size();i++)
		int inicial =ciuIni;
		int times=0;
		while(hor[h].enables.size())
		{	
			//cout<<"b"<<endl;
			//int i=0;
			ruleta=0;
			vProb.clear(); vCoste.clear();
			hor[h].camino.push_back(inicial);
			hor[h].enables.remove(inicial+65);
			//cout<<"\n sizeeee ::  "<<hor[h].enables.size()<<endl;
			/*for(int i=0;i<columnas;i++)
			{
				vCoste[i]=0;	
			}*/
			for(auto formi:hor[h].enables)	
			{
				vCoste[(formi)-65]=pow(MF[inicial][(formi)-65],alfa)* pow(MV[inicial][(formi)-65],beta); 
				ruleta += vCoste[(formi)-65];
				//cout<<vCoste[(formi)-65]<<endl;
	//			i++;
			}
			//for(int i=0;i<columnas;i++)
			//	cout<<vCoste[i]<<endl;
			//cout<<endl;
			//cout<<"\n suma: "<<ruleta<<endl<<"   \n probabilidades: "<<endl;	
			for(auto formi:hor[h].enables)	
			{
				vProb[(formi)-65]=(vCoste[(formi)-65]/ruleta);
				//cout<<vProb[(formi)-65]<<endl;
			}
			double r= genRandom(0,1);
			//cout<<"\n Numero aleatorio :"<<r<<endl;
			double acu=0;
			for(auto formi:hor[h].enables)
			{
				acu+=vProb[(formi)-65];
				//cout<<"acumnulado: "<<acu<<endl;
				if(r<=acu)
				{	
					inicial=(formi)-65; 
					break;
				}
			}
            //cout<<"El siguiente es ... :"<<inicial<<endl;
		}	
	}
}

void calcFitness(vector<hormiga> &F)
{
	for(int i=0;i<F.size();i++)
	{
		double acc=0;
		for(int j=0;j<F[i].camino.size()-1;j++)
				acc+=MT[F[i].camino[j]][F[i].camino[j+1]]; 
		F[i].fitness=acc;
	}
}
double eval(double q, hormiga f, int i,int j)
{
	for(int n=0;n<f.camino.size()-1;n++)
	{
		//cout<<i<<"###"<<j<<endl;
		//cout<<"camino"<<n<<" "<<f.camino[n]<<endl;
		if((f.camino[n]==i && f.camino[n+1]==j) || (f.camino[n]==j && f.camino[n+1]==i))
		{
			//cout<<i<<"***"<<j;
			cout<<" + "<<(q/f.fitness);
			return (q/f.fitness);
		}	
	}
	cout<<" + "<<0;
	return 0;
		
}
void updateFermonasp(double q, double p, int columnas, vector<hormiga> &h)
{
	cout<<"\n \nActualizando Matriz de fermononas \n"<<endl;
	for(int i=0;i<columnas;i++)
	{
		//cout<<" "<<endl;
		double tmp=0;
		for(int j=0;j<columnas;j++)
		{
			if(i!=j)
			{
				cout<<i<<" "<<j<<" = ";
				tmp=p*MF[i][j];
				cout<<tmp<<"";
				for(int k=0;k<h.size();k++)
				{
					tmp+=eval(q,h[k],i,j);
				}
				MF[i][j]=tmp;		
				cout<<endl;
			}
		}
	}
}

int main()
{
	srand (time(NULL));
	int cantHormigas=4;
	vector<hormiga> hormiguero;
	int alfa=1; int beta=1; double Q=1; double p= 0.99; int maxitera=100;
	cout<<"alfa "<<alfa<<endl;
	cout<<"beta "<<beta<<endl;
	cout<<"Q "<<Q<<endl;
	cout<<"p "<<p<<endl;
	int filas = 10; int columnas = 10; double feromona=0.1;
	start(filas,columnas,feromona);
	printMat("\n Matriz de distancia \n \n", MT, filas, columnas);
	printMat("\n Matriz de feromonas \n \n", MF, filas, columnas);
	matrixVisilibidad(filas, columnas);
	printMat("\n Matriz de visibilidad \n \n", MV, filas, columnas);
	//startHormiguero(hormiguero,cantHormigas, filas);
	//printHormiguero("\n Imprimiendo Hormiguero \n",hormiguero);
	int times=0;
	while(times<200)
	{
		cout<<"***************** Iteracion"<<times<<"<<<<<<<<<<<<<"<<endl;
		startHormiguero(hormiguero,cantHormigas, filas);
		printHormiguero("\n  Hormiguero  inicial\n",hormiguero);
		int ciuIni=3;//D
		//Matriz de feromonas por visibilidad
		ruleta(alfa, beta, ciuIni,columnas,hormiguero);
		//printHormiguero("\n Nuevo Hormiguero \n",hormiguero);
		calcFitness(hormiguero);
		//printHormiguero("\n Nuevo Hormiguero \n",hormiguero);
			sort(hormiguero.begin(), hormiguero.end(),compare);
		printHormiguero("\n Nuevo Hormiguero \n",hormiguero);
		cout<<"\n Mejor Hormiga :\n";printHormiga(hormiguero[0]);	
		updateFermonasp(Q,p,columnas,hormiguero);
		//printHormiguero("\n Hormiguero A Evaluar \n",hormiguero);
		//printMat(" \n Nueva Matriz de feromonas\n \n",MF, filas, columnas);
		times++;
	}
	return 0;
}