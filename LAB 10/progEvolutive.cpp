#include <iostream>
#include <vector>
#include <string>
#include <cmath>	
#include <algorithm>
#include <cstdlib>
#include <list>


using namespace std;

typedef struct {
	string cadena;
	bool active=false;
}estado;

typedef struct {
	vector<estado> vectEstados;
	double fit=0;
	int inicial=0;
	vector<int> VA;
}individuo;

void printIndividuo(string s , individuo a)
{
	cout<<s;
	for(int i =0 ; i< a.vectEstados.size();i++ )
	{
		cout<<a.vectEstados[i].cadena<<"  ";
	}
	cout<<"inicial: "<<a.inicial<<"  fitness:  "<<a.fit<<endl;
}
string evalIndividuo(string cad,individuo & ind)
{
	string result;
	for(int i = 0;i< cad.size();i++)
	{
		int estIni=ind.inicial;
		estado ini = ind.vectEstados[estIni];
		if(ini.cadena[1]==cad[i])
		{
			result+=ini.cadena[3];
			char Next = ini.cadena[5];
			estado ini = ind.vectEstados[Next-65];
		}
		else
		{
			if(ini.cadena[2]==cad[i])
			{
				result+=ini.cadena[4];
				char Next = ini.cadena[6];
				estado ini = ind.vectEstados[Next-65];
			}
		}
	}
	int count=0;
	for(int k=0;k<result.size();k++)
	{
		if(cad[k+1]==result[k])
			count++;
	}
	ind.fit=count;
	return result;
}

void mutacion(individuo & ind)
{
	int prob= rand()%100;
	if(prob<=20)
	{
		int r= rand() % ind.VA.size();
		int est= ind.VA[r];
		estado elegido = ind.vectEstados[est];
		elegido.cadena[0]='0';
		elegido.active=false;
	}
	if(prob>20 && prob<=40)
	{
		int est=ind.inicial;
		while(est==ind.inicial)
		{
			int r= rand() % ind.VA.size();
			est= ind.VA[r];
		}	
		ind.inicial=est;
	}
	if(prob>40 && prob<=60)
	{
		


		//ind.cadena
	}
	if(prob>60 && prob<=80)
	{

	}
	if(prob>80)
	{
		list<int>inactivos;
		inactivos.resize(4);
		inactivos.push_back(0);
		inactivos.push_back(1);
		inactivos.push_back(2);
		inactivos.push_back(3);
		for(auto a : ind.VA)
		{
			inactivos.remove(a);
		}
		int r = rand()%inactivos.size();
		std::list<int>::iterator it1 = inactivos.begin();
		int t=0;
		while(t<r)
			++it1;
		ind.vectEstados[*it1].active=true;
	}
}
individuo getRandomInd(int numEstado, int tamEstado)
{				
	vector<int> VectorActives;
	individuo nuevo;
	int activeForce=0;
	for(int i =0;i<numEstado;i++)
	{
		estado A ;
		A.cadena.resize(tamEstado);
		for(int j=1;j<tamEstado-2;j+=2)
		{
			//Asegurar entradas diferentes
				float ran = rand() % 2;
				if(ran ==0)
				{ 
					A.cadena[j]='N';
					A.cadena[j+1]='S';
				}
				else
				{
					A.cadena[j]='S';
					A.cadena[j+1]='N';	
				}
		}
		//Asegurar por lo menos 2 Activos;
		if(activeForce<2)
		{
			A.cadena[0]='1';	
			activeForce++;
			A.active=true;
			VectorActives.push_back(i);	
		}
		else
		{
			float ran = rand() % 2;
			A.cadena[0]=ran +'0';
			if(ran==1) 
			{
				VectorActives.push_back(i);	A.active=true;
			}
		}
		nuevo.vectEstados.push_back(A);	
	}

	for(int i =0;i<numEstado;i++)
	{
		//* Seleccion de estados;
		for(int l=0;l<2;l++)
		{
			int pos = rand() % VectorActives.size();
			int estado=VectorActives[pos];
			nuevo.vectEstados[i].cadena[5+l]='A'+estado;	
		}	
		//Eligiendo el inicial 
		int pos = rand() % VectorActives.size();
		int estado=VectorActives[pos];
		nuevo.inicial=estado;		
	}
	nuevo.VA=VectorActives;
	return nuevo;
}

int main()
{
	srand (time(NULL));
	int numeroEstados= 4;
	int tamanoEstados = 7;
	int numeroIndividuos = 10; 
	vector<individuo> pobIndividuos;
	for(int i=0;i<numeroIndividuos;i++)
	{
		individuo r = getRandomInd(numeroEstados,tamanoEstados);
		pobIndividuos.push_back(r);	
		printIndividuo("",r);
	}
	//string input="NSSNSSNSSNSSNSS";
	string input="NSSNSSNSS";
	for(auto r : pobIndividuos)
	{

		cout<<evalIndividuo(input,r)<<" ";
		printIndividuo("",r);
	}
	

	//cout<<'A'-65<<endl;
	return 0;
}