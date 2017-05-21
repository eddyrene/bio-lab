#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "decimal.h"

using namespace dec;
using namespace std;

double Pi= 3.14159;

typedef decimal<10> BIGDECIMAL; 

typedef struct {
	vector<double> val,varianza;
	BIGDECIMAL fit;
	BIGDECIMAL porcent;
}individuo;

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

BIGDECIMAL evalVect(std::vector<double> v)
{
	double x= v[0];double y= v[1];
	/*cout<<" "<<-cos(x)*cos(y)*exp(-pow((x-Pi),2)-pow((y-Pi),2));*/
	//double r = 100*pow((x*x - y),2) + pow((1- x),2); 
	double r = -1*cos(x)*cos(y)*exp(-1*pow((x-Pi),2)-pow((y-Pi),2));

 	BIGDECIMAL t =decimal_cast<10>(r);
	//cout<<"   x:"<<x<<"      y:"<<y<<"      r"<<r<<endl;
	return t;
}

void calcFitness(vector<individuo> &m)
{
	for(int i=0;i< m.size(); i++)
	{
		BIGDECIMAL f=evalVect(m[i].val);
		m[i].fit=f ;//*10000000;
		//cout<<"f:  "<<m[i].fit<<endl;
	}
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

void printVectIndividuosVari(string a, vector<individuo> m)
{
	cout<<a<<endl;
	for(int i = 0; i< m.size() ; i++)
	{
		for(int j=0; j< m[i].val.size(); j++)
		{
			cout<<m[i].val[j]<<"    ";
			cout<<m[i].varianza[j]<<"    ";
		}

		cout<<endl;
	}
}

void printVectIndividuosFitness(string a, vector<individuo> m)
{
	cout<<a<<endl;
	for(int i = 0; i< m.size() ; i++)
	{
		for(int j=0; j< m[i].val.size(); j++)
		{
			cout<<m[i].val[j]<<"  ";
		}
		//cout<<"  "<<std::setprecision(48)<<m[i].fit<<endl;
		cout<<"  "<<m[i].fit<<endl;
	}
}

void printVectIndividuosFitnessPorcent(string a, vector<individuo> m)
{
	cout<<a<<endl;
	for(int i = 0; i< m.size() ; i++)
	{
		for(int j=0; j< m[i].val.size(); j++)
		{
			cout<<m[i].val[j]<<"  ";
		}
		cout<<"  "<<m[i].fit<<"    "<<m[i].porcent<<endl;
	}
}
double genRandom(double li, double ls)
{
	//srand (time(NULL));
	return li + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(ls-li)));
}

void ruleta(vector<individuo> &v)
{
    cout<<"\nSelección de Individuos - Método de la Ruleta"<<endl;
    vector<BIGDECIMAL> acumulador;
    for (int i =0; i < v.size() ; i++)
    	acumulador.push_back(v[i].fit);
    BIGDECIMAL min (*(min_element(acumulador.begin(), acumulador.end())));

    min=min.abs();
    cout<<"este es el minimo elemento"<<min<<endl;

    for (int i =0; i < v.size() ; i++)
    {
    	v[i].fit+=min;
    	//cout<<"nuevo fitness     "<<v[i].fit<<endl;	
    }

    cout<<"Se sumó el minimo valor para calcular porcentajes \n ";
    printVectIndividuosFitness("Imprimiendo nuevos fitness", v);

    double a =0;
    BIGDECIMAL sum_ruleta(0);
    BIGDECIMAL cerito(0);
    cerito*=0;
    sum_ruleta*=0;
    //double sum_ruleta=0;    
    for (int i =0; i < v.size() ; i++)
    {
    	//cout<<"debe coincidir    "<<v[i].fit<<endl;	
        sum_ruleta+= v[i].fit;
    }
    cout<<"\n sumatoria  "<< sum_ruleta<<endl;
    
    if(sum_ruleta==cerito)
    {
    	for (int i =0; i < v.size() ; i++)
    	{
    		v[i].porcent=100;
    	}	
    }
    else
    {
    	for (int i =0; i < v.size() ; i++)
    	{
	    	//cout<<"division     "<<v[i].fit <<"   "<<v[i].fit *100<< "    entre   "<<sum_ruleta<<endl;
	        v[i].porcent=(( v[i].fit*100 )/sum_ruleta);
	        //cout<<"porcentaje"<<v[i].porcent<<endl;
	    }
    	for (int i =0; i < v.size() ; i++)
    		v[i].fit-=min;
	
    }
    
}

int chooseRandomParent(std::vector<individuo> &v)
{
  BIGDECIMAL num (rand()%100);
  cout<<"Numero para padre Ramdom:  "<< num<<endl;
  BIGDECIMAL s(0);
  s*=0;
  for (int i =0; i < v.size() ; i++)
  {
        s += v[i].porcent;
       // cout<<"s"<<s<<endl;
  	if(num<s)
  		return i;
  }
  return v.size() - 1;
}

individuo cross2ind(individuo &n , individuo &m) 
{
	individuo nn;
	//cout<<"val"<<(n.val[0] + m.val[0])/2<<endl;
	vector<double> datos,varians;
	for(int i=0;i<n.val.size();i++)
	{
		double sum= (n.val[i] + m.val[i])/2;
		//cout<<"sum "<<sum<<endl;
		datos.push_back((sum));
		double sum2= sqrt(n.varianza[i]+m.varianza[i]);
		//cout<<"sum2 "<<sum2<<endl;
		varians.push_back(sum2);
	}
	nn.val=datos ;nn.varianza=varians;
	return nn;
}

void mutation(individuo &n,double sizepob, double li, double ls)
{
	//(double l_i, double l_s, double desvio, double delta, double aleatorio)
	cout<<"\n \n Se realizo la mutacion \n";
	double k = 2*sqrt(sizepob);
	double deltaVar =  1/sqrt(k);
	cout<<"delta  "<<deltaVar<<endl;
	double ale= genRandom(li,ls);
	cout<<"El numero radom   "<<ale<<endl;
	double dn = valor_x(li,ls,deltaVar,0.01,ale);
	cout<<"Desvio Normal   \n "<<dn<<"  "<<exp(dn)<<endl;
	double newDes = n.varianza[0]*exp(dn);
	cout<<"Nueva varianza \n "<<newDes<<endl;
	for(int i =0;i<n.val.size();i++)
	{
		double a= genRandom(li,ls);
		double b= valor_x(li,ls,newDes,0.01,a);
		cout<<"b "<<b<<endl;
		n.val[i]+= b;
		n.varianza[i]=newDes;
	}
}
void printIndividuo(string a, individuo m)
{
	cout<<a<<endl;
	for(int i =0 ;i < m.val.size(); i++)
		cout<<m.val[i]<<"  "<< m.varianza[i]<<" ";
	//cout<<"   "<<m.fit<<"  "<<m.porcent;
}
void reproduction(vector<individuo> &pob, double limi, double lims)
{
	int padre= chooseRandomParent(pob);
	int madre= chooseRandomParent(pob);
	cout<<"\n Padre \n "<<padre<<"  "<<pob[padre].val[0]<<"  "<<pob[padre].val[1]<<endl;
	cout<<"\n Madre \n "<<madre<<"  "<<pob[madre].val[0]<<"  "<<pob[madre].val[1]<<endl;
	cout<<"\n Cruzamiento \n";
	individuo child=cross2ind(pob[padre],pob[madre]);
	printIndividuo("\n Hijo Generado",child);
	mutation(child,pob.size(), limi, lims);
	if(child.val[0]<limi)
		child.val[0]=limi;
	if(child.val[1]<limi)
		child.val[1]=limi;
	if(child.val[0]>lims)
		child.val[0]=lims;	
	if(child.val[1]>lims)
		child.val[1]=lims;
	printIndividuo("\n",child);
	//void mutation(individuo &n,double sizepob, double li, double ls)
	pob.push_back(child);
}
bool OrderByMayor(individuo a, individuo b)
{
	if(a.fit<b.fit)
		return true;
	return false;
}

int main()
{
	///std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	//setprecision();
	srand (time(NULL));
	cout<<"algoritmo de Mu+1 , Seccion extintiva"<<endl;
	double li= -10;
	double ls= 10;
	double desvio_ini = 0.3;
	int iteraciones = 100;
	vector<individuo> individuosT;
	//vector<double> individuoT1;

	int numInd= 50;
	int lamda= 70;
	cout<<"Generando individuosT"<<endl;
	for(int i=0; i<numInd ; i++)
	{
		double x = genRandom(li,ls);
		double y = genRandom(li,ls);
		vector<double> v,d; individuo ind;
		v.push_back(x);v.push_back(y);
		d.push_back(desvio_ini);d.push_back(desvio_ini);
		ind.varianza=d;
		ind.val=v;
		individuosT.push_back(ind);
	}
	printVectIndividuosVari("\n Primera Poblacion ", individuosT);	cout<<endl;
	int c=0;
	while(c<iteraciones)
	{
		cout<<"**************      Iteracion "<<c<<"*****************"<<endl;
		printVectIndividuosVari("\n Los Individuos iniciales ", individuosT);
		calcFitness(individuosT);
		printVectIndividuosFitness(" \n Imprimiendo fitness", individuosT);
		ruleta(individuosT);
		printVectIndividuosFitnessPorcent("\n Imprimiendo Porcentajes", individuosT);
		for(int i =0; i<lamda; i++ )
			reproduction(individuosT, li, ls);
		printVectIndividuosFitness("\n Nueva Poblacion ", individuosT);
		calcFitness(individuosT);
		sort(individuosT.begin(), individuosT.end(), OrderByMayor);
		printVectIndividuosFitness("\n Individuos Ordenados ", individuosT);
		for(int i =0; i<lamda; i++ )
			individuosT.pop_back();
		printVectIndividuosFitness("\n Mejores Individuos ", individuosT);
		c++;
	}	
}	