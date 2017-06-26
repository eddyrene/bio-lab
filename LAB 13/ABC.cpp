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


static int Dim=2;
typedef struct 
{
	double val[2];
	double fEval;
	double fit;
}Sol;

typedef pair<int,int> tupla;
typedef vector<vector<double> > mat;
typedef vector<Sol> Soluciones;

double genRandom(double li, double ls)
{
	return li + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(ls-li)));
}
void printSol(string s,Sol a)
{
	cout<<s;
	cout<<a.val[0]<<" "<<a.val[1]<<" "<<a.fEval<<" "<<a.fit<<endl;
}
void printSoluciones(string s,Soluciones E)
{
	cout<<s;
	for(int i=0;i<E.size();i++)
	{
		printSol(to_string(i)+")   ",E[i]);
	}
}
void calcfEvalSol(Sol &a)
{
	 a.fEval=pow(a.val[0],2)+pow(a.val[1],2);
}
void calcFit(Sol &a)
{
	if(a.fEval>=0)
		a.fit=1/(1+a.fEval);
	else
		a.fit=1+abs(a.fEval);
}
void calcfEvalSoluciones(Soluciones &E)
{
	for(auto &e:E)
		calcfEvalSol(e);
}
void calcFitSoluciones(Soluciones &E)
{
	for(auto &e:E)
		calcFit(e);	
}
void startPop(Soluciones &A, int CS)
{
	for(int i=0;i<CS;i++)
	{
		Sol n_a;
		n_a.val[0]= genRandom(-5,5);
		n_a.val[1]= genRandom(-5,5);
		n_a.fEval=0;
		n_a.fit=0;
		A.push_back(n_a);
	} 
}
void genCandidatas(Soluciones & A,Soluciones & cand,int CS, int D, int SN)
{
	for(int i=0;i<CS;i++)
	{
		double fi=genRandom(-1,1);
		int j = round((genRandom(0,D-1)));
		int k = round(genRandom(0,SN-1));
		if(k!=i)
		{
			Sol n;
			n.val[j]=A[i].val[j]+ fi * (A[i].val[j]-A[k].val[j]);
			n.fEval=0;
			n.fit=0;
			cand.push_back(n);
		}
		else
			int k = round(genRandom(0,SN-1));
	}
}
int main()
{
	srand (time(NULL));
	int CS=6; //tamaño de colmena
	int D=2 ; //Numero de variables
	int L=6; //num de iteracciones antes de abandonar la fuente
	int MCN=5; //Maximo numero de ciclos que itera el algorimo
	int SN=3; //numero de soluciones
	Soluciones A;
	Soluciones cand;
	startPop(A,CS);
	//cout<<"size"<<A.size()<<endl;
	printSoluciones("\n Soluciones inicial \n\n", A);
	calcfEvalSoluciones(A);
	calcFitSoluciones(A);
	printSoluciones("\n Calculando fEval y fitness \n\n", A);
	genCandidatas(A,cand,CS,D,SN);
	printSoluciones("\n Soluciones Candidatas \n\n", cand);
	calcfEvalSoluciones(cand);
	calcFitSoluciones(cand);
	printSoluciones("\n Calculando fEval y fitness \n\n", cand);

	return 0;
}