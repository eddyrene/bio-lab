#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

double Pi= 3.1415;

double normal(double x, double desvio)
{
	double retorno = -0.5 * ((x/desvio)* (x/desvio));
	retorno = exp(retorno);
	retorno= retorno/ (desvio* sqrt(6.283184));
	return retorno;
}
double valor_x(double l_i, double l_s, double desvio, double delta, double aleatorio)
{
	double area=0;
	double aux_sum, aux = normal(l_i, desvio);
	for(double i = l_i + delta; i < l_s ; i+=delta)
	{
		aux_sum = normal(i, desvio);
		area+= (aux+aux_sum);
		if((area * (delta/2))>aleatorio)
		{
			return i ;	
		}
		aux= aux_sum;
	}
	return std::numeric_limits<double>::min();
}

double fitness(std::vector<double> v)
{
	double x= v[0];double y= v[1];
	return -cos(x)*cos(y)*exp(-pow((x-Pi),2)-pow((y-Pi),2));
}

void printVect(string a, vector<double> t)
{
	cout<<a<<endl;
	for(int i =0 ; i<t.size();i++)
	{
		cout<<t[i]<<" ";
	}
}
void printMat(string a, vector<vector<double> > m)
{
	cout<<a<<endl;
	for(int i = 0; i< m.size() ; i++)
	{
		for(int j=0; j< m[i].size(); j++)
		{
			cout<<m[i][j]<<" ";
		}
		cout<<endl;
	}
}

double genRandom(double li, double ls)
{
	return li + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(ls-li)));
}
int main()
{

	srand (time(NULL));
	cout<<"algoritmo de Mu+1 , Seccion extintiva"<<endl;

	double li= -100;
	double ls= 100;
	double desvio_ini = 0.3;
	int iteraciones = 1000;
	
	vector<std::vector<double> > individuosT;
	vector<double> individuoT1;

	int numInd= 5;
	cout<<"Generando individuosT"<<endl;
	for(int i=0; i<numInd ; i++)
	{
		double x = genRandom(li,ls);
		double y = genRandom(li,ls);
		vector<double> individuo;
		individuo.push_back(x);individuo.push_back(y);
		individuosT.push_back(individuo);
	}	

	printMat("\n Los Individuos iniciales ", individuosT);

	cout<<"generando individuo T1 "<<endl;
	double x = genRandom(li,ls);
	double y = genRandom(li,ls);
	individuoT1.

	int contador=0;
	int tt=0;
}