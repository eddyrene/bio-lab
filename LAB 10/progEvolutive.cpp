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
	string outString;
}individuo;

void printIndividuo(string s , individuo a);

individuo mutacion(individuo ind)
{
	individuo ar=ind;
	ar.VA=ind.VA;	
	//printIndividuo("realmente copia", ar);
	int prob= rand()%100;
	int type=0;
	if(prob<=20)
	{
		cout<<type<<endl;
		int r= rand() % ar.VA.size();
		int est= ar.VA[r];
		//estado elegido = ar.vectEstados[est];
		ar.vectEstados[est].cadena[0]='0';
		ar.vectEstados[est].active=false;
		vector<int> tmp= ar.VA;
		ar.VA.clear();
		for(int i=0;i<tmp.size();i++)
		{
			if(ar.vectEstados[i].active==true)
				ar.VA.push_back(i);
		}
		//cout<<"hasta aqui"<<endl;
		if(ar.VA.size()>1)
		{
			if(ar.inicial==est)
			{	
				//cout<<"tamaño"<<ar.VA.size()<<endl;
				//cout<<rand()%ar.VA.size()<<endl;
				ar.inicial=ar.VA[rand()%ar.VA.size()];
			}
			for(int i =0;i<ar.VA.size();i++)
			{
				cout<<ar.VA.size()<<" "<<endl;
				// Seleccion de estados;
				for(int l=0;l<2;l++)
				{
					int estado=ar.VA[rand() % ar.VA.size()];
					ar.vectEstados[ar.VA[i]].cadena[5+l]='A'+estado;	
				}	
			}
		}
		else
		{
			ar.inicial=ar.VA[0];
		}
	}
	if(prob>20 && prob<=40)
	{
		type=1;
		cout<<type<<endl;
		int est=ind.inicial;
		if(ar.VA.size()>=2)
		{
			while(est==ind.inicial)
			{
				int r= rand() % ar.VA.size();
				est= ar.VA[r];
			}	
			ar.inicial=est;	
		}
		else
		{
			int est=ind.inicial;
		}
	}

	if(prob>40 && prob<=60)
	{
		type=2;
		cout<<type<<endl;
		int r= rand() % ar.VA.size();
		int est= ar.VA[r];
//		estado elegido = ind.vectEstados[est];
		char tmp=ar.vectEstados[est].cadena[1];
		ar.vectEstados[est].cadena[1]=ar.vectEstados[est].cadena[2];
		ar.vectEstados[est].cadena[2]=tmp;
	}
	if(prob>60 && prob<=80)
	{
		type=3;
		cout<<type<<endl;
		//if(ar.VA.size()!=0)
		int r= rand() % ar.VA.size();
		int est= ind.VA[r];
//		estado elegido = ind.vectEstados[est];
		if(ar.vectEstados[est].cadena[3] == 'S')
		{
			ar.vectEstados[est].cadena[3]='N';
			//cout<<"se cambio a N"<<endl;
		}	
			
		else
			ar.vectEstados[est].cadena[3]='S';
	}
	if(prob>80)
	{
		type=4;
		cout<<"type  "<<type<<endl;
		list<int>inactivos;
		//inactivos.resize(4);
		inactivos.push_back(0);
		inactivos.push_back(1);
		inactivos.push_back(2);
		inactivos.push_back(3);
		//cout<<"activos"<<ar.VA.size()<<endl;
		for(auto a : ar.VA)
		{
			inactivos.remove(a);
		}
		//cout<<"inactivos "<<inactivos.size()<<endl;
		if(inactivos.size()==0)
		{		}
		else
		{
			int r = rand()%inactivos.size();
			list<int>::iterator it1 = inactivos.begin();
			int t=0;
			while(t<r)
			{
				++it1;
				t++;
			}
			//cout<<*it1<<endl;
			ar.vectEstados[*it1].active=true;
			ar.vectEstados[*it1].cadena[0]='1';
			ar.VA.push_back(*it1);

			//Actualizo Estados Activos;
			/*for(int i =0;i<ar.vectEstados.size();i++)
			{
				/ Seleccion de estados;
				for(int l=0;l<2;l++)
				{
					int pos = rand() % ar.VA.size();
					int estado=ar.VA[pos];
					ar.vectEstados[i].cadena[5+l]='A'+estado;	
				}	
				int pos = rand() % ar.VA.size();
				int estado=ar.VA[pos];
				ar.inicial=estado;		
			}*/

		}
	}
	cout<<"tipo de mutacion  "<<type<<endl;
	return ar;
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

void reproduccion(string a ,std::vector<individuo> &v, int tam)
{
	cout<<a;
	for(int i=0;i<tam;i++)
	{
		individuo n = mutacion(v[i]);
		v.push_back(n);
		//cout<<"agrego"<<endl;
	}
}
void printIndividuo(string s , individuo a)
{
	cout<<s;
	for(int i =0 ; i< a.vectEstados.size();i++ )
	{
		cout<<a.vectEstados[i].cadena<<"  ";
	}
	cout<<"inicial: "<<a.inicial<<"  fitness:  "<<a.fit<<endl;
}
void printfPob(string a, std::vector<individuo> &v)
{
	cout<<a;
	int h=0;
	for(auto &i: v)
	{
		cout<<h<<") ";
		for(int j=0;j<i.vectEstados.size();j++)
		{
			cout<<i.vectEstados[j].cadena<<"  ";
		}

		cout<<"inicial: "<<i.inicial<<"  fitness:  "<<i.fit<<" numero de activos: "<<i.VA.size()<<endl;		
		h++;
	}
}
void printfPobResult(string a, std::vector<individuo> &v)
{
	cout<<a;
	int h=0;
	for(auto &i: v)
	{
		cout<<h<<") ";
		for(int j=0;j<i.vectEstados.size();j++)
		{
			cout<<i.vectEstados[j].cadena<<"  ";
		}
		cout<<"inicial: "<<i.inicial<<"  fitness:  "<<i.fit<<" numero de activos: "<<i.VA.size()<<" outString "<<i.outString<<endl;		
		h++;
	}
}
bool OrderByMayor(individuo a, individuo b)
{
	if(a.fit>b.fit)
	{
		return true;
	}
	return false;
}

void evalIndividuo(string cad,individuo &ind)
{
	string result;
	result.clear();
	int estIni=ind.inicial;
	estado ini = ind.vectEstados[estIni];
	for(int i = 0;i< cad.size();i++)
	{
		if(ini.cadena[1]==cad[i])
		{
			result+=ini.cadena[3];
			char Next = ini.cadena[5];
			ini= ind.vectEstados[Next-65];
		}
		else
		{
			if(ini.cadena[2]==cad[i])
			{
				result+=ini.cadena[4];
				char Next = ini.cadena[6];
				ini= ind.vectEstados[Next-65];
			}
		}
	}
	int count=0;
	for(int k=0;k<result.size()-1;k++)
	{
		if(cad[k+1]==result[k])
			count++;
	}
	ind.fit=count;
	ind.outString=result;
}
void EvalPoblacion(string input, std::vector<individuo> &v)
{
	for(int i=0;i<v.size();i++)
		evalIndividuo(input,v[i]);
}
int main()
{
	srand (time(NULL));
	int numeroEstados= 4;
	int tamanoEstados = 7;
	int numeroIndividuos = 15; 
	vector<individuo> pobIndividuos;
	int iteraciones=20;
	for(int i=0;i<numeroIndividuos;i++)
	{
		individuo r = getRandomInd(numeroEstados,tamanoEstados);
		pobIndividuos.push_back(r);		
		printIndividuo("",r);
	}
	int c=0;
	while(c<iteraciones)
	{
		cout<<"**************      Iteracion "<<c<<"*****************"<<endl;
		reproduccion("Los individuos se reproducen \n", pobIndividuos,numeroIndividuos);
		printfPob("Nueva Poblacion \n", pobIndividuos);
		string input="NSSNSSNSSNSSNSS";
		//string input="NSSNSSNSS";
		EvalPoblacion(input,pobIndividuos);
		printfPob("evaluando a los individuoss \n", pobIndividuos);
		pobIndividuos.size();
		vector<individuo> vn;
		vn.clear();
		for(int i=0;i<pobIndividuos.size();i++)
		{
			if(pobIndividuos[i].VA.size()>2)
				vn.push_back(pobIndividuos[i]);
		}
		pobIndividuos.clear();
		pobIndividuos=vn;
		sort(pobIndividuos.begin(), pobIndividuos.end(), OrderByMayor);
		printfPob("Ordenando individuos \n", pobIndividuos);
		int lim =pobIndividuos.size();
		for(int i=0;i<(pobIndividuos.size()-(numeroIndividuos+1));i++)
			pobIndividuos.pop_back();
		printfPobResult("Los más aptos\n ", pobIndividuos);	
		c++;
	}
	return 0;
}