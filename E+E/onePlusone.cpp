#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;


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
	return 100*pow((x*x - y),2) + pow((1- x),2);
}

void printVect(string a, vector<double> t)
{
	cout<<a<<endl;
	for(int i =0 ; i<t.size();i++)
	{
		cout<<t[i]<<" ";
	}
}
int main()
{
	srand (time(NULL));
	cout<<"algoritmo de 1+1 , Seccion extintiva"<<endl;

	double li= -2.048;
	double ls= 2.048;
	double desvio_ini = 0.3;
	int iteraciones = 10;
	vector<double> individuo;
	vector<double> individuoT1;

	double x = li + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(ls-li)));
	double y = li + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(ls-li)));
	individuo.push_back(x);individuo.push_back(y);
	printVect("\n Individuo inicial", individuo);


	int tt=0;
	while(tt<iteraciones)
	{
		int times =0;	
		int success=0; int failures =0;
		double c = 0.817;
		while(times<10)
		{
			//double dist = valor_x(-10000, 10000, desvio_ini,0.5, individuo);
			double dist1 = 0.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.9-0.1)));//valor_x(-10000, 10000, desvio_ini,0.5, individuo);
			dist1= dist1+desvio_ini;
			double dist2 = 0.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.9-0.1)));//valor_x(-10000, 10000, desvio_ini,0.5, individuo);
			dist1= dist2+desvio_ini;
			//cout<<"valor a añadir "<<dist<<endl;
			individuoT1.clear();
			individuoT1.push_back(dist1);individuoT1.push_back(dist2);
			individuoT1[0]= individuo[0]+ dist2;
			individuoT1[1]= individuo[1]+ dist2;
			printVect("\n \n Individuo Generado", individuoT1);	

			double fitOriginal=  fitness(individuo);
			cout<<"\n \n fitOriginal : "<<fitOriginal<<endl;
			double fitGenerado=  fitness(individuoT1);
			cout<<"\n fitGenerado : "<<fitGenerado<<endl;
			if(fitOriginal < fitGenerado)
			{
				individuo[0]=individuoT1[0];
				individuo[1]=individuoT1[1];
				success++;
				printVect(" \n Vencedor: Hijo ", individuo);
			}
			else
			{
				failures++;
				printVect("\n Vencedor: Padre ", individuo);
			}
			times++;
		}	
		double ps = success /(success+failures);
		if(ps<1/5)
			desvio_ini= desvio_ini* c;
		if(ps>1/5)
			desvio_ini= desvio_ini/ c;
		tt++;
			
	}
	return 0;
}